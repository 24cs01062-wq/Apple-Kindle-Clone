#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
class book{
     public:
        vector<string>b;
        string name;
        int page=0;
        book(vector<string>&b,string name){
            this->b=b;
            this->name=name;
        }   
        bool nextpage(){
            if(page==b.size()-1)return 0;
            page++;
            return 1;
        }
        bool prevpage(){
          if(page==0)return 0;
          page--;
          return 1;
        }
        bool go_to(int idx){
          if(idx>=0 && idx<b.size()){
              page=idx;
              return 1;
          }
          return 0;
        }
        void display(){
             cout<<b[page]<<" ";
        }

         
};
class library{
   private:
       vector<book*>lib;
       book* active;
   public:

   void add(book* b){
     lib.push_back(b);
   }
   bool del(book* b){
       for(int i=0;i<lib.size();i++){
            if(lib[i]==b){
                lib.erase(lib.begin()+i);
                return 1;
            }
       }
       return 0;
   }
   void display(){
     for(int i=0;i<lib.size();i++){
          cout<<i+1<<"."<<lib[i]->name<<"\n";
     }
   }
   bool select(string name){
       for(int i=0;i<lib.size();i++){
          if(lib[i]->name==name){
                  active=lib[i];
                  return 1;
          }
     }
     return 0;
   }
   bool read(){
     if(active==NULL)return 0;
     active->display();
     return 1;
   }
   bool flip(bool t){
     if(active==NULL)return 0;
     if(t==1)active->nextpage();
     else active->prevpage();
     return 0;
   }
   bool search(int idx){
       bool s=active->go_to(idx);
       return s;
   }

};
int main(){
    vector<string>arr;
    arr.push_back("abc");
    arr.push_back("bcd");
    arr.push_back("cde");
    arr.push_back("def");
   library *l=new library();
   l->add(new book(arr,"King"));
   l->add(new book(arr,"Queen"));
   l->display();
   l->select("King");
   


}