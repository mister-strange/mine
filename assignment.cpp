
//Author: Roshan Kumar
//M.Tech. Cyber Security
#include<bits/stdc++.h>

using namespace std;
int nodeid=1,c_node=0,cnt;
struct node
{
    time_t now;  //time stamp
    string own_name,addr,mob,ph;
    float val;
    int node_no;
    node *ref_node_id;
    int child_node_id;
    //node *ref_child_node_id;
   vector<node *>ref_child_node;
};
string encryptDecrypt(string s)   //Algorithm to encrypt and decrypt owner data
{
    char key = 'R';
    string out  = s;
    for(int i=0;i<s.size();i++)
    {

        out[i]=s[i]^key;
    }
    return out;
}
node * newnode(node *root)  //Function to create new node
{
    node *tmp = new node;
    cout<<"enter name"<<endl;
    string name;
    cin>>name;
    tmp->own_name=encryptDecrypt(name);
    cout<<"enter address"<<endl;
    string address;
    cin>>address;
    tmp->addr=encryptDecrypt(address);
    cout<<"enter Phone no."<<endl;
    string phone;
    cin>>phone;
    tmp->ph=encryptDecrypt(phone);
    cout<<"enter mobile no."<<endl;
    string mobile;
    cin>>mobile;
    tmp->mob=encryptDecrypt(mobile);
    tmp->ref_node_id = root;
    tmp->child_node_id=nodeid++;
    root->ref_child_node.push_back(tmp);
cout<<"Node succesfully inserted";
}
node * postorderRec(node *head,int id)  //tree traversal to find address of required node
{

	if (head->ref_child_node.empty())
		if(head->node_no==id)
                return head;
	else
	{
		for (vector<node *>::iterator iter = head->ref_child_node.begin(); iter != head->ref_child_node.end(); iter++)
		{
			postorderRec(*iter,id);
			if(head->node_no==id)
                return head;
		}

	}

}
int chain_longest(node *head)   //calculates the longest chain possible in tree
{

	if (head == NULL)
	{
		cout << "empty tree" << endl;
		return 0;
	}

	if (head->ref_child_node.empty())
		cnt++;
	else
	{
		for (vector<node *>::iterator iter = head->ref_child_node.begin(); iter != head->ref_child_node.end(); iter++)
		{
			chain_longest(*iter);
		}
		cnt++;
	}
	return cnt;

}
int main()
{
    int i;
    int choice;

    node *head = NULL;
    do{
    cout<<endl;
    cout<<"Enter Your Choice"<<endl;

    cout<<"1: Create first node"<<endl;
    cout<<"2: Create multi-set of first node"<<endl;
    cout<<"3: Add a new node"<<endl;
    cout<<"4: Find longest chain of main node"<<endl;
    cout<<"5: Break a node"<<endl;
    cout<<"6: Exit"<<endl;
    cin>>choice;



    switch(choice)
    {
        case 1:{
                cout<<"Enter owner name"<<endl;
                string t_own_name;
                cin>>t_own_name;
                cout<<"Enter address"<<endl;
                string t_add;
                cin>>t_add;
                cout<<"Enter Mobile No."<<endl;
                string mobile;
                cin>>mobile;
                cout<<"Enter Phone No."<<endl;
                string phone;
                cin>>phone;
                cout<<"Enter value"<<endl;
                float val;
                cin>>val;
                node *tmp = new node;
                tmp->own_name = encryptDecrypt(t_own_name);
                tmp->addr = encryptDecrypt(t_add);
                tmp->mob=encryptDecrypt(mobile);
                tmp->ph=encryptDecrypt(phone);
                tmp->node_no = 1;
                tmp->ref_node_id = NULL;
                tmp->child_node_id = 0;
                //tmp->ref_child_node=NULL;
                head = tmp;
                break;
        }
       case 2:{
                cout<<"Enter Number of sets to be created for this node"<<endl;
                int sets;
                cin>>sets;

                for(i=0;i<sets;i++)
                {
                    cout<<"Inserting first node of set: "<<i+1<<endl;
                    cout<<"Enter owner name"<<endl;
                string t_own_name;
                cin>>t_own_name;
                cout<<"Enter address"<<endl;
                string t_add;
                cin>>t_add;
                cout<<"Enter Mobile No."<<endl;
                string mobile;
                cin>>mobile;
                cout<<"Enter Phone No."<<endl;
                string phone;
                cin>>phone;
                cout<<"Enter value"<<endl;
                float val;
                cin>>val;
                node *tmp  = new node;

                head->ref_child_node.push_back(tmp);
                tmp->own_name = encryptDecrypt(t_own_name);
                tmp->addr = encryptDecrypt(t_add);
                tmp->mob=encryptDecrypt(mobile);
                tmp->ph=encryptDecrypt(phone);
                nodeid++;
                tmp->node_no = nodeid;
                tmp->ref_node_id = head;
                tmp->child_node_id = 0;

                //break;

                }

            break;
       }
       case 3:
        {
            cout<<"Enter parent node id where new node to be inserted";
            int id;
            cin>>id;
            //cout<<head->node_no;

           node * tmp = postorderRec(head,id);
           newnode(tmp);
           c_node++;
            break;
        }
       case 4:
        {
            int ct = chain_longest(head);
            cout<<"Longest chain from root node"<<endl;
            cout<<ct+c_node<<endl;
            break;
        }


       case 5:
        {
            cout<<"Enter Node id to be break"<<endl;
            int id ;
            cin>>id;
            node *tmp = postorderRec(head,id);

            free(tmp);
            cout<<"Node deleted successfully"<<endl;
            break;
        }

        case 6:exit(0);
                break;
       default: cout<<"Invalid Choice"<<endl;
                break;

    }
    }while(choice!=6);
    return 0;
}
