#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "parrots.cpp"

#define inbuf_len (1 << 16)
#define outbuf_len (1 << 16)
#define MAX_N 128
#define MAX_M 10000

static int message[MAX_N];
static int encoded_message[MAX_M];
static int output_message[MAX_N];
static int N, M, O;
static int max_expansion, channel_range;

void send(int x) {
  if (M == MAX_M) {
    fprintf(stdout, "Encoded message too long\n");
    fflush(stdout);
    exit(0);
  }
  encoded_message[M++] = x;
}

void output(int y) {
  if (O < N) {
    output_message[O++] = y;
  }
}

static void sort_message(int d) {
  for (int i = 0; i < M - 1; ++i) {
    int bi = i;
    int b = encoded_message[i];
    for (int j = i + 1; j < M; ++j) {
      if (((d == 0) && (encoded_message[j] < b)) ||
          ((d == 1) && (encoded_message[j] > b))) {
        b = encoded_message[j];
        bi = j;
      }
    }
    int t = encoded_message[i];
    encoded_message[i] = encoded_message[bi];
    encoded_message[bi] = t;
  }
}

static void random_shuffle() {
  for (int i = 0; i < M - 1; ++i) {
    int p = rand() % (M - i);
    int t = encoded_message[i];
    encoded_message[i] = encoded_message[i + p];
    encoded_message[i + p] = t;
  }
}

static void shuffle(int method) {
  if (method == 0) {
    sort_message(0);
  } else if (method == 1) {
    sort_message(1);
  } else {
    random_shuffle();
  }
}

static void check_encoded_message() {
  if (M > max_expansion * N) {
    printf("Encoded message too long.\n");
    exit(0);
  }
  for (int i = 0; i < M; ++i) {
    if (encoded_message[i] < 0 || encoded_message[i] > channel_range) {
      printf("Bad encoded integer\n");
      exit(0);
    }
  }
}

static int check_output() {
  if (O != N) {
    return 0;
  }
  for (int i = 0; i < N; ++i) {
    if (message[i] != output_message[i]) {
      return 0;
    }
  }
  return 1;
}

static int read_int() {
  int x;
  if (scanf("%d", &x) != 1) {
    printf("Invalid input file.\n");
    exit(0);
  }
  return x;
}

static void run_encoder_phase() {
  int tt = read_int();
  max_expansion = read_int();
  channel_range = read_int();
  int r = read_int();
  srand(r);

  printf("%d\n", tt);
  for (int t = 0; t < tt; ++t) {
    N = read_int();
    for (int i = 0; i < N; ++i) {
      message[i] = read_int();
    }
    int p = read_int();
    M = 0;
    encode(N, message);
    check_encoded_message();
    shuffle(p);
    printf("%d\n", N);
    printf("%d\n", M);
    for (int i = 0; i < M; ++i) {
      printf("%d%c", encoded_message[i], i + 1 == M ? '\n' : ' ');
    }
    printf("%d\n", p);
  }
}

static void run_decoder_phase() {
  int tt = read_int();
  for (int t = 0; t < tt; ++t) {
    N = read_int();
    M = read_int();
    for (int i = 0; i < M; ++i) {
      encoded_message[i] = read_int();
    }
    read_int();
    O = 0;
    decode(N, M, encoded_message);
    putchar('\n');
    if (!check_output()) {
      printf("Incorrect\n");
      exit(0);
    }
  }
  printf("Correct.\n");
}

int main(int argc, char **argv) {
  int tmp;
  char *inbuf, *outbuf;
  inbuf = (char *)malloc(inbuf_len * sizeof(char));
  outbuf = (char *)malloc(outbuf_len * sizeof(char));
  tmp = setvbuf(stdin, inbuf, _IOFBF, inbuf_len);
  tmp = setvbuf(stdout, outbuf, _IOFBF, outbuf_len);
  (void)tmp;

  int run_id = 0;
  if (argc >= 2) {
    run_id = atoi(argv[1]);
  }

  if (run_id == 0) {
    run_encoder_phase();
  } else {
    run_decoder_phase();
  }

  return 0;
}
