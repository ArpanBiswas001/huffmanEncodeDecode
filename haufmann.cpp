#include<bits/stdc++.h>
using namespace std;
class Node{
	public: 
	char data;
	int cost;
	Node* right;
	Node* left;
	
	Node(char _data,int _cost,Node* _right=nullptr,Node* _left=nullptr){
		this->data=_data;
		this->cost=_cost;
		this->left=_left;
		this->right=_right;
	}
};
//min heap on basis of cost. low cost->high priority.
struct comp{
	bool operator()(Node* a,Node* b){
		return a->cost>b->cost;
	}
};
void encode(Node* root,string str,unordered_map<char,string>& mp){
	if(root==NULL)
		return;
	if(root->left==NULL && root->right==NULL){
		mp[root->data]=str;
	}
	encode(root->left,str+'0',mp);
	encode(root->right,str+'1',mp);
}
void decode(Node* root,string ans,int& index){
	if(root==NULL)
		return;
	if(root->left==NULL && root->right==NULL){
		cout<<root->data;
		return;
	}
	index++;
	if(ans[index]=='0')
		decode(root->left,ans,index);
	else
		decode(root->right,ans,index);
}
void buildTree(string s){
	unordered_map<char,int> mp;
	for(auto e:s){
		mp[e]++;
	}
	
	priority_queue<Node*,vector<Node*>,comp> pq;
	
	for(auto e:mp){
		Node* newNode=new Node(e.first,e.second);
		pq.push(newNode);
	}
	
	while(pq.size()!=1){
		Node* top1=pq.top(); pq.pop();
		Node* top2=pq.top(); pq.pop();
		
		Node* newNode=new Node('/0',(top1->cost+top2->cost),top2,top1);
		
		pq.push(newNode);
	}
	Node* root=pq.top();
	
	unordered_map<char,string> encodeMap;
	
	encode(root,"",encodeMap);
	for(auto m:encodeMap){
		cout<<m.first<<"----"<<m.second<<endl;
	}
	string ans="";
	for(auto e:s){
		ans+=encodeMap[e];
	}
	cout<<ans<<endl;
	
	int index=-1;
	while(index<(int)ans.size()-2)
		decode(root,ans,index);
}
int main(){
	string s="Huffman coding is a data compression algorithm.";
	
	buildTree(s);
	
	return 0;
}

/*
o----111
H----11011
l----11010
g----1100
a----101
m----1000
n----0111
u----01101
f----00010
r----00011
h----000011
c----00000
s----1001
.----000010
p----001010
t----00100
i----0011
e----001011
 ----010
d----01100
*/
//00100100101110111101011101010001011111100010011110010000011101110001101010101011001101011011010101111110000111110101111001101000110011011000001000101010001010011000111001100110111111000111111101
