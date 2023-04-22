#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include "animals.hpp"

using namespace std;

/* ------------------------------ */
/* ------ CLASS NodeAnimal ------ */
/* ------------------------------ */

/* CONSTRUTORES */

NodeAnimal::NodeAnimal(string name, string scientificName, string classification)
{
    /* Função 1 */
    if (!name.empty()){
        this->name=name;
    }
    if (!scientificName.empty()){
        this->scientificName=scientificName;
    }
    if (!classification.empty()){
        this->classification=classification;
    }
    this->vertebrate=false;
    this->left=nullptr;
    this->right=nullptr;
    this->characteristics.clear();
    
}

NodeAnimal::NodeAnimal(string name, string scientificName)
{
    /* Função 2 */
    if (!name.empty()){
        this->name=name;
    }
    if (!scientificName.empty()){
        this->scientificName=scientificName;
    }
    this->classification="";
    this->vertebrate=false;
    this->characteristics.clear();

}

/* DESTRUTOR */

NodeAnimal::~NodeAnimal()
{
    /* Função 3 */
    delete left;
    delete right;
}

/* MÉTODOS GET */

string NodeAnimal::getName() const
{
    /* Função 4 */
    return name;
}

string NodeAnimal::getScientificName() const
{
    /* Função 5 */
    return scientificName;
}

string NodeAnimal::getClassification() const
{
    /* Função 6 */
    return classification;
}

bool NodeAnimal::getVertebrate() const
{
    /* Função 7 */
    return vertebrate;
}

vector<string> NodeAnimal::getCharacteristics() const
{
    /* Função 8 */
    return characteristics;
}

/* MÉTODOS SET */

void NodeAnimal::setName(string name)
{
    /* Função 9 */
    if(!name.empty()){
        this->name=name; 
    }
}

void NodeAnimal::setClassification(string classification)
{
    /* Função 10 */
    if (!classification.empty()){
        this->classification=classification;
    }
}

void NodeAnimal::setVertebrate(bool vertebrate)
{
    /* Função 11 */
    if (vertebrate==1 || vertebrate==0){
        this->vertebrate=vertebrate;
    }
}

/* OUTROS MÉTODOS */

void NodeAnimal::addCharacteristic(string characteristic)
{
    /* Função 12 */
    if (!characteristic.empty()){
        this->characteristics.push_back(characteristic);
    }
}

int NodeAnimal::removeCharacteristic(string characteristic)
{
    /* Função 13 */
    if (characteristic.empty()){
        return -1;
    }

    auto it = find(this->characteristics.begin(), this->characteristics.end(), characteristic);
    if (it==this->characteristics.end()){
        return 0;
    }

    else{
        this->characteristics.erase(it);
        return 1;
    }

}

/* ------------------------------ */
/* ------- CLASS TreeBST -------- */
/* ------------------------------ */

/* CONSTRUTOR */

TreeBST::TreeBST()
{
    /* Função 14 */
    this->root=nullptr;
}

/* DESTRUTOR */

TreeBST::~TreeBST()
{
    /* Função 15 */
    delete root;
}

/* MÉTODOS GET */

NodeAnimal* TreeBST::getRoot()
{
    /* Função 16 */
    return root;
}

/* MÉTODOS SET */

void TreeBST::setRoot(NodeAnimal *newRoot)
{
    /* Função 17 */
    if (newRoot!=nullptr){
        this->root=newRoot;
    }  
    
}

/* OUTROS MÉTODOS */

int TreeBST::insert(NodeAnimal *treeNode, NodeAnimal *newNoA)
{
    /* Função 18 */
    if (treeNode==NULL){
        this->root=newNoA;
        return 0;
    }

    else{
        if (newNoA->getScientificName()<treeNode->getScientificName()){
            if (treeNode->left==NULL){
                treeNode->left=newNoA;
                return 0;
            }

            else{
                return insert(treeNode->left, newNoA);
            }
        }

        if (newNoA->getScientificName()>treeNode->getScientificName()){
            if (treeNode->right==NULL){
                treeNode->right=newNoA;
                return 0;
            }

            else{
                return insert(treeNode->right, newNoA);
            }

        }
    }

    return -1;

}

int TreeBST::insert(NodeAnimal *newNoA)
{
    if (newNoA == nullptr)
    {
        return(-1);
    }
    else
    /*Chama função recursiva com a raiz*/
    {
        return(insert(root, newNoA));
    }
}

NodeAnimal* TreeBST::searchNode(string scientificName)
{
    /* Função 19 */
    if (scientificName.empty()){
        return NULL;
    }

    NodeAnimal* current = root;

    while (current != NULL) {
        if (current->getScientificName() == scientificName) {
            return current;
        } else if (current->getScientificName() < scientificName) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return NULL;
}

int TreeBST::totalAnimals(NodeAnimal* root,bool vert)
{
    /* Função 20 */
    if (root == NULL) {
        return 0;
    }

    int total = 0;

    if (root->getVertebrate() == vert) {
        total = 1;
    }
    
    total += totalAnimals(root->left, vert);
    total += totalAnimals(root->right, vert);

    return total;
}

int TreeBST::totalAnimals(bool vert)
{
    return(totalAnimals(root, vert));
}

int TreeBST::size(NodeAnimal* root)
{
    /* Função 21 */
    if (root == NULL) {
        return 0;
    }
    else {
        int count = 1; // soma 1 para o nó atual
        count += size(root->left); // chama a função para o filho esquerdo
        count += size(root->right); // chama a função para o filho direito
        return count;
    }

}

int TreeBST::size()
{
    return(size(root));
}

vector<NodeAnimal*> TreeBST::searchCharacteristic(NodeAnimal* root, string charac)
{
    /* Função 22 */
    
    vector<NodeAnimal*> result;

    if (root == NULL) {
        return result;
    }
    
    if (charac.empty()) {
        return result;
    }
    
    int tam=(int)root->getCharacteristics().size();
    for (int i=0; i<tam; i++){
        if (root->getCharacteristics()[i]==charac){
            result.push_back(root);
        }
    }
    
    searchCharacteristic(root->left, charac);
    searchCharacteristic(root->right, charac);

    return result;


}

vector<NodeAnimal*> TreeBST::searchCharacteristic(string charac)
{
    vector<NodeAnimal*> result;
    if(!charac.empty())
    {
        result = searchCharacteristic(root, charac);
    }
    else
    {
        result.clear();
    }
    return(result);
}

int TreeBST::commonCharacteristic(NodeAnimal* root, string charac1, string charac2)
{
    /* Função 23 */

    if (root == nullptr) {
        return 0;
    }

    if (charac1.empty() || charac2.empty()) {
        return -1;
    }

    int count = 0;

    if (find(root->getCharacteristics().begin(), root->getCharacteristics().end(), charac1)!=root->getCharacteristics().end() && find(root->getCharacteristics().begin(), root->getCharacteristics().end(), charac2)!=root->getCharacteristics().end()){
        count++;
    }

    count += commonCharacteristic(root->left, charac1, charac2);
    count += commonCharacteristic(root->right, charac1, charac2);

    return count;

}

int TreeBST::commonCharacteristic(string charac1, string charac2)
{
    int result;
    if(charac1.empty() || charac2.empty())
    {
        result = 0;
    }
    else
    {
        result = commonCharacteristic(root, charac1, charac2);
    }
    return(result);
}

int TreeBST::import(const string filename)
{
    if (filename.empty())
    {
        return -1;
    }
    
    ifstream f(filename);
    
    if (!f)
    {
        return -1;
    }
    
    string scientificName, name;
    
    NodeAnimal *n;
    int result;

    string s;
    stringstream ss, ssd;
    char delim = ',';

    while (getline(f, s))
    {
        s.pop_back();
        ss.clear();
        ss << s;
    
        getline(ss, scientificName, delim);
        getline(ss, name, delim);
    
        n = new NodeAnimal(name, scientificName );

        if (!n)
        {
            delete n;
            f.close();
            return -1;
        }

        result = insert(n);
    
        if (result == -1)
        {
            delete n;
            f.close();
            return -1;
        }
    }

    f.close();
    
    return 0;
}

priority_queue<string,vector<string>, greater<string>>* TreeBST::createDictionary(NodeAnimal* root)
{
    /* Função 24 */
    




}

int TreeBST::positionDictionary(string scientificName)
{
    /* Função 25 */   
}

int TreeBST::updateCharacteristicsFromFile(DecisionTree &treeB, const string filename)
{
    /* Função 26 */    
}

int TreeBST::updateCharacteristicsFromClassification(DecisionTree &treeB, string scientificName)
{
    /* Função 27 */
}