#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
class book{
     public:
        vector<string>b;
        string author;
        string date;
        string name;
        int page;
        book(vector<string>&b,string name,string author,string date){
          this->author=author;
          this->date=date;
            page=0;
            this->b=b;
            this->name=name;
        } 
        void updatebook(vector<string>&arr){
          b=arr;
          return;
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
class applelib{
  private:
       map<string,book*>mp;
       
   public:
  void add(string name,vector<string>&arr,string author,string date){
      if(mp.find(name)!=mp.end()){
          mp[name]->updatebook(arr);
          return;
      }
      mp[name]=new book(arr,name,author,date); 
      return;
   }
   bool del(string name){
       if(mp.find(name)==mp.end())return 0;
        book * temp=mp[name];
        mp.erase(name);
        delete temp;
        return 1;
   }
   book* search(string name){
     return mp[name];

   }
   void display(){
      cout<<"Books in Kindle:"<<"\n";
      for(auto m:mp){
        cout<<m.first<<"\n";
      }
   }
};
 applelib* apple=new applelib();
 class readlist{
     private:
       vector<book*>lib;
       book* active;
       applelib* a;
   public:
   readlist(applelib*a){
    active=nullptr;
    this->a=a;
   }
   void add(string name){
     if(a->search(name)==nullptr){
      cout<<"Doesnt exist\n";
      return;
     }
     lib.push_back(a->search(name));
     return;
   }
   bool del(string name){
       for(int i=0;i<lib.size();i++){
            if(lib[i]->name==name){
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
   string passcode;
   cin>>passcode;
   if(passcode=="Alpha016"){
      cout<<"Welcome Raam!!!"<<"\n";
      cout<<"Do u want to add or remove???"<<"\n";
      bool l;
      cin>>l;
      if(l==1){
      cout<<"How many Items would you like to add"<<"\n";
      int n;
      cin>>n;
      while(n>0){
          string name;
          vector<string>arr(300);
          string date;
          string author;
          cout<<"Name of the book: ";
          cin>>name;
          cout<<"\n";
          cout<<"Author of the book:  ";
          cin>>author;
          cout<<"\n";
          cout<<"Date of publishing: ";
          cin>>date;
          cout<<"\n";
          apple->add(name,arr,author,date);
          n--;
      }
    }
    else{
        cout<<"How many Items would u like to remove"<<"\n";
        int m;
        cin>>m;
        while(m>0){
           string name;
           cin>>name;
           bool n=apple->del(name);
           if(n==0){
            cout<<"Doesnt exist"<<"\n";
           }
           m--;
        }
    }
     apple->display();

   }
   else{
      cout<<"Welcome user!!";
      
   }
   return 0;

}
