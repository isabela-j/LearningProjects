#pragma once
#include <QVector>
#include "Laptop.h"
#include <algorithm>
#include <vector>
template<class T>
class Repo
{
public:
    Repo()=default;

    ~Repo();

    int findIndexByPhoto(const QString & t_name);

    bool addLaptop(T * lap);

    bool removeLaptop(T * lap);

    void removeAllLaptops(const QString &s) ;

    bool updateLaptop(const QString &s, T * lap);

    QString stringForAll() const;

    QString showLaptopFromIndex(const int& index) const;

    std::vector<T*> getElements() { return m_repo.toStdVector(); }
    
    const QVector<T*> &getrepo(){return m_repo;}

    int getLength() const;

    T* getLaptopFromIndex(const int& index) const{ return m_repo[index];}

private:
    QVector<T*> m_repo;
};


template <class T>
Repo<T>::~Repo() {
    for (auto it = m_repo.cbegin(); it < m_repo.cend(); it++)
    {
        delete* it;
    }
    cout << "Repo destructor was called. \n";
}

///This function tells us if we already have a laptop in the repository
/// OBS: A LAPTOP IS UNIQUE BY ITS LINK TO ITS PICTURE
///In: repo( the repository), t_name( link to its picture)
///Out: index- the position of where the offer was found,  -1 if there is no offer with the given parameters
template <class T>
int Repo<T>::findIndexByPhoto(const QString& t_name)
{
    std::vector<T*> elems= m_repo.toStdVector();
    const auto it = std::find_if(elems.begin(), elems.end(), [&](const Laptop* t_elem) { return t_elem->getPhoto() == t_name; });
    int index = -1;
    if (it != elems.end())
        index = std::distance(elems.begin(), it);
    return index;
}

///This function adds a laptop to the repository
///In: repo(the repository), lap- the laptop that we want to be added
///Out: true- if the object was added, false- otherwise (this means that the laptop is already in the repository)
template <class T>
bool Repo<T>::addLaptop(T* lap) {
    int index = findIndexByPhoto(lap->getPhoto());
    if (index == -1) {
        m_repo.append(lap);
        return true;
    }
    return false;
}

/// This function removes  a laptop which is in the repository
/// In: repo(the repository), lap- the laptop that we want to be removed
///Out: true- if the object was removed, false- otherwise (this means that the laptop is not in the repository)
template <class T>
bool Repo<T>::removeLaptop(T* lap) { 
    int index = findIndexByPhoto(lap->getPhoto());
    if (index != -1)
    {
        m_repo[index]->setQuantity(m_repo[index]->getQuantity() - 1);
        if (m_repo[index]->getQuantity() == 0)
        {
            delete m_repo[index];
            m_repo[index] = nullptr;
            m_repo.remove(index);
        }
        return true;
    }
    return false;
}

/// This function updates a laptop which is in the repository
/// In: repo(the repository), s- the link of the laptop which hs to be updated, lap- the new laptop
///Out: true- if the object was updated, false- otherwise (this means that the laptop is not in the repository)
template <class T>
bool Repo<T>::updateLaptop(const QString & s, T* lap) {
    int index = findIndexByPhoto(s);
    if (index != -1)
    {
        m_repo[index] = lap;
        return true;
    }
    return false;
}

/// Creates a string with all of the specifications of the laptops from the repository
template <class T>
QString Repo<T>::stringForAll() const {
    QString str;
    for (int it = 0; it < m_repo.size(); it++)
         str+=m_repo[it]->toString();
    return str;
}

/// Displays the string for the laptop which is at position "index" ( if the index is correct)
template <class T>
QString Repo<T>::showLaptopFromIndex(const int& index)const {
    if(index>=0 && index<m_repo.size()){
       return  m_repo[index]->toString();
    }
    else return "Index not valid.\n";
}

/// Gets the length of the repository
template< class T>
int Repo<T>::getLength() const{
    return m_repo.size();
}

///removes all laptops with a given picture, not just one from quantity
template<class T>
void Repo<T>::removeAllLaptops(const QString &s)
{
    int index = findIndexByPhoto(s);
    if(index!=-1)
    {
        delete m_repo[index];
        m_repo[index] = nullptr;
        m_repo.remove(index);
    }
}
