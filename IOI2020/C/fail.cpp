int n = x.size();
	// m = 1
	int m = x[0].size();
	vector<vector<int>> answer(n, vector<int>(m, -1));


	long long ans = 0;
	if (m == 1){
		for (int i = 0; i < n; i++){
			answer[i][0] = 0;
		}
		allocate_tickets(answer);
		vector<int> y;
		for (int i = 0; i < n; i++){
			y.push_back(x[i][0]);
		}
		sort(y.begin(), y.end());
		int mid = ((int)y.size())/2;
		for (int i = 0; i < mid; i++){
			ans += (y[mid]-y[i]);
		}
		for (int i = mid+1; i < (int)y.size(); i++){
			ans += (y[i]-y[mid]);
		}
	} else {
		for (int i = 0; i < n; i++){
			small[i] = big[i] = 0;
			for (int j = 1; j < m; j++){
				if (x[i][j] < x[i][small[i]]){
					small[i] = j;
				} 
				if (x[i][j] > x[i][big[i]]){
					big[i] = j;
				}
			}
		}

		for (int round = 1; round <= n/2; round++){
			int ibest = -1, jbest = -1, with = -1;
			bool imin;
			for (int i = 0; i < n; i++){
				if (taken[i]) continue;
				for (int j = i+1; j < n; j++){
					if (taken[j]) continue;
					// consider i and j: imin jmax, imax jmin

					int cand = abs(x[i][small[i]]-x[j][big[j]]);
					if (ibest == -1 || cand > with){
						with = cand;
						ibest = i; 
						jbest = j;
						imin = 1;
					}
					cand = abs(x[i][big[i]]-x[j][small[j]]);
					if (ibest == -1 || cand > with){
						with = cand;
						ibest = i;
						jbest = j;
						imin = 0;
					}
				}
			}
			// cout << ibest << ' ' << jbest << ' ' << imin << endl;
			// take ibest, jbest 
			ans += with;
			taken[ibest] = 1;
			taken[jbest] = 1;
			// cout << small[ibest] << endl;
			if (imin == 0){
				answer[ibest][big[ibest]] = 0;
				answer[jbest][small[jbest]] = 0;
			} else {
				answer[ibest][small[ibest]] = 0;
				answer[jbest][big[jbest]] = 0;
			}
		}
		allocate_tickets(answer);
	}