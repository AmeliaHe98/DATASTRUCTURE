#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
       cout<< length()<<endl;
}

void path::BFS(){
	// initialize working vectors
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));
    queue<pair<int,int>> q;
    q.push(start);
    V[start.second][start.first] = true;
    
    while(!q.empty()){
        pair<int,int> temp_queue = q.front();
        vector<pair<int,int>> visited = neighbors(temp_queue);
        q.pop();
        for(unsigned i = 0; i< visited.size(); i++){
            if(good(V,temp_queue,visited[i] )){
                q.push(visited[i]);
                P[visited[i].second][visited[i].first]=temp_queue;
                V[visited[i].second][visited[i].first]=true;
                
            }
        }
}
    pathPts = assemble(P,start,end);
    cout<< pathPts.size()<<endl;
}

PNG path::render(){

    for(unsigned i = 0; i< pathPts.size(); i++){
        pair<int,int> temp = pathPts[i];
        
//        for(int i = temp.first; i < temp.first+4;  i++){
//            for(int j = temp.second; j < temp.second+4;  j++){
                RGBAPixel *curr = image.getPixel(temp.first, temp.second);
                curr->r = 255;
                curr->g = 0;
                curr->b  = 0;
//        }
//        }
        
    }
    return image;

}

vector<pair<int,int>> path::getPath() { return pathPts;}

int path::length() { return pathPts.size();}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    int width = image.width();
    int height = image.height();
    int curr_x = curr.first;
    int curr_y = curr.second;
    int next_x = next.first;
    int next_y = next.second;

    if(next_x>=0&&next_x<width&&next_y>=0&&next_y<height){
       
        if(v[next.second][next.first]){
            return false;
        }
        else{
            RGBAPixel *Pcurr = image.getPixel(curr_x,curr_y);
            RGBAPixel *Pnext = image.getPixel(next_x,next_y);
            if(closeEnough(*Pcurr, *Pnext)){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }
}



vector<pair<int,int>> path::neighbors(pair<int,int> curr) {

	vector<pair<int,int>> n ;
    int x = curr.first;
    int y = curr.second;
    //general case
    pair<int,int> above = make_pair (x,(y-1));
    pair<int,int> below = make_pair (x,(y+1));
    pair<int,int> left = make_pair ((x-1),y);
    pair<int,int> right = make_pair ((x+1),y);
    n.push_back(left);
    n.push_back(below);
    n.push_back(right);
    n.push_back(above);
    
    return n;

}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {
    vector<pair<int,int>> path;
	stack<pair<int,int>> S;

    if(p[e.second][e.first]==e){
        path.push_back(s);
    }
    else{
        S.push(e);
        pair<int,int> temp = S.top();
        while(temp!=start){
            pair<int,int> prev = S.top();
            int prev_x = prev.first;
            int prev_y = prev.second;
            prev = p [prev_y][prev_x];
            temp = prev;
            S.push(temp);
        }
        S.push(s);
    
    while(S.top()!=end){
        pair<int,int> top = S.top();
        path.push_back(top);
        S.pop();
    }
        
    }
    return path;
    
}

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist = (p1.r-p2.r)*(p1.r-p2.r) + (p1.g-p2.g)*(p1.g-p2.g) +
               (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
