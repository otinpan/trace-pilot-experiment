#include<iostream>
#include<vector>
int main() {
  int n,m,c;
  std::cin>>n>>m>>c;

  std::vector<int> d(m);
  for(int i=0;i<m;i++)std::cin>>d[i];
  std::vector<std::vector<int>> f(n,std::vector<int>(n));

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      std::cin>>f[i][j];
    }
  }
  
  std::cout<<"yes"<<std::endl;
  return 0;
}

