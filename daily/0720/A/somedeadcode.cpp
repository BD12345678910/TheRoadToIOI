vector<int> xrem;
    for (auto [x, V]: xlight){
        if ((int)V.size() > B){
            xheavy[x] = V;
            xrem.push_back(x);
        }
    }
    for (int x : xrem){
        xlight.erase(x);
    }
    vector<int> yrem;
    for (auto [x, V]: ylight){
        if ((int)V.size() > B){
            yheavy[x] = V;
            yrem.push_back(x);
        }
    }
    for (int x : yrem){
        ylight.erase(x);
    }

    for (auto [x, V]: xlight){
        for (pair<int,int> [_, v] : V){
            xmaxlight[x] = max(xmaxlight[x], v);
        }
    }
    for (auto [x, V]: ylight){
        for (pair<int,int> [_, v] : V){
            ymaxlight[x] = max(ymaxlight[x], v);
        }
    }
    for (auto [x, V]: xheavy){
        for (pair<int,int> [_, v] : V){
            xmaxheavy[x] = max(xmaxheavy[x], v);
        }
        xlazy[x] = 0;
    }
    for (auto [x, V]: yheavy){
        for (pair<int,int> [_, v] : V){
            ymaxheavy[x] = max(ymaxheavy[x], v);
        }
        ylazy[x] = 0;
    }