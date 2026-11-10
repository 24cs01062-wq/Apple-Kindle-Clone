#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <iomanip>
#include<map>
using namespace std;
class book{
    private:
       string title;
       int totalpages;
       string date;
       vector<bool>bookmark;
       int currentpage;
       string author;
       vector<string>pages;
       vector<bool>viewed;
    public:
        book(string title,string author,vector<string>& pages,string date){
            bookmark.resize(pages.size(),false);
            viewed.resize(pages.size(),false);
            currentpage=0;
            this->date=date;
            this->author=author;
            totalpages=pages.size();
            this->pages=pages;
            this->title=title;
        }
        vector<string> bookcontent(){
            return pages;
        } 
        string bookname(){
            return title;
        }
        string authorname(){
            return author;
        }
        string issuedate(){
            return date;
        }
        void updatebook(vector<string>& arr){
               this->pages=pages;
        }
        int page(){
            return currentpage;
        }
        void bookinfo(){
            cout<<"Title:"<<title<<"\n";
            cout<<"Author:"<<author<<"\n";
            cout<<"No of pages:"<<totalpages<<"\n";
            return;
        }
        void viewpage(){
            cout<<"Current page:"<<currentpage<<"\n";
            cout<<pages[currentpage]<<"\n";
            viewed[currentpage]=true;
            return; 
        }
        void prevpage(){
            if(currentpage==0){
                cout<<"Invalid page number";
                return;
            }
            currentpage--;
        }
        void nextpage(){
            if(currentpage==totalpages-1){
                cout<<"Invalid page number";
                return;
            }
            currentpage++;
        }
        void gotopage(int idx){
            if(idx<0 || idx>=totalpages){
                cout<<"Invalid page index";
                return;
            }
            currentpage=idx;
        }
        void setbookmark(){
            bookmark[currentpage]=true;
            return;
        }
        void del(int idx){
            if(idx<0 || idx>=totalpages){
                cout<<"Invalid page index";
                return;
            }
            if(bookmark[idx]==false){
                cout<<"No bookmark on this page\n";
                return;
            }
            bookmark[idx]=false;
            return;
        }
        double bookcomp(){
            int count=0;
            for(int i=0;i<totalpages;i++){
                if(viewed[i]==true)count++;
            }
            double comp=(double)(count*100)/totalpages;
            return comp;
        }
        void viewallbookmark(){
            cout<<"All bookmark for "<<title<<"\n";
            for(int i=0;i<totalpages;i++){
                if(bookmark[i]==true){
                    cout<<"->"<<i<<"\n";
                }
            }
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
      mp[name]=new book(name,author,arr,date); 
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
    if(mp.find(name)==mp.end())return nullptr;
     return mp[name];

   }
   void display(){
      cout<<"Books in Kindle:"<<"\n";
      for(auto m:mp){
        cout<<m.first<<"\n";
      }
   }
   void saveLibrary() {
    ofstream file("library.txt");

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << mp.size() << "\n";

    for (auto &entry : mp) {
        book* bk = entry.second;

        file << quoted(bk->bookname()) << "\n";
        file << quoted(bk->authorname()) << "\n";
        file << quoted(bk->issuedate()) << "\n";

        file << bk->page() << "\n";
        file << bk->bookcontent().size() << "\n";

        //  for (const string &text : bk->b) {
        //      file << quoted(text) << "\n";
        //  }
    }

    file.close();

    cout << "Library saved successfully!\n";
}
void loadLibrary() {
    ifstream file("library.txt");

    if (!file) {
        cout << "No existing library found.\n";
        return;
    }

    int n;
    if (!(file >> n) || n < 0) {
        cout << "Invalid library file.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        string name, author, date;
        int page;
        int totalPages;

        if (!(file >> quoted(name)
                   >> quoted(author)
                   >> quoted(date)
                   >> page >> totalPages) || totalPages < 0) {
            cout << "Invalid book data.\n";
            return;
        }

        vector<string> pages(totalPages);

        for (int j = 0; j < totalPages; j++) {
            if (!(file >> quoted(pages[j]))) {
                cout << "Invalid page data.\n";
                return;
            }
        }

        add(name, pages, author, date);

        if (totalPages > 0) {
            mp[name]->gotopage(page);
        }
    }

    file.close();

    cout << "Library loaded successfully!\n";
}
};
 applelib* apple=new applelib();
 class readlist{
     private:
       vector<book*>lib;
       map<string,int>fav;
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
            if(lib[i]->bookname()==name){
                lib.erase(lib.begin()+i);
                return 1;
            }
       }
       return 0;
   }
   void display(){
     for(int i=0;i<lib.size();i++){
          cout<<i+1<<"."<<lib[i]->bookname()<<"\n";
     }
   }
    void setactive(string name){
        for(int i=0;i<lib.size();i++){
            if(lib[i]->bookname()==name){
                active=lib[i];
                cout<<"Opening "<<name<<"..."<<"\n";
                active->viewpage();
                return; 
            }
        } 
        cout<<name<<" doesnt exist in your Library!!!"<<"\n"; 
     }
     
    void close(){
        if(active==nullptr){
            cout<<"No books are currently active!!"<<"\n";
            return;
        }
        active=nullptr;
        cout<<"Book Closed!!"<<"\n";
    }
    void setfav(){
        if(active==nullptr){
            cout<<"No book opened!!"<<"\n";
            return;
        }
        fav[active->bookname()]=1;
     }
        void bookinfo(){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return;
            }
            return active->bookinfo();
        }
        void gotoprevpage(){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return;
            }
            active->prevpage();
            active->viewpage();
        }
        void gotonextpage(){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return;
            }
            active->nextpage();
            active->viewpage();
        }
        void gotopage(int idx){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return;
            }
            active->gotopage(idx);
            active->viewpage();
        } 
        void setbookmark(){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return;
            }
            active->setbookmark();
        }
        void delbookmark(int idx){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return;
            }
            active->del(idx);
        }
        double bookcomp(){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return 0.0;
            }
            return active->bookcomp();
        }
        void viewallbookmark(){
            if(active==nullptr){
                cout<<"No book opened!!"<<"\n";
                return;
            }
            active->viewallbookmark();
        }
        void search(string name){
           
        for(int i=0;i<lib.size();i++){
            if(lib[i]->bookname()==name){
                cout<<name<<"exist in your Library!!!"<<"\n";
                return; 
            }
        } 
        cout<<name<<" doesnt exist in your Library!!!"<<"\n"; 
     
        }
        
 };
int main(){
     apple->loadLibrary();
   string passcode;
   cout<<"Enter the passcode:"<<"\n";
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
    apple->saveLibrary();
     apple->display();

   }
   else{
      cout<<"Welcome user!!";
      
   }
   return 0;

}
