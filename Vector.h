#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdlib>

#define CHOP_SIZE 10

using namespace std;

template <class T> 
class Vector
{
	  template <class U> friend ostream &operator<<(ostream &, const Vector<U> &);
	  template <class U> friend istream &operator>>(istream &, Vector<U> &);
public:
		Vector();
		Vector(size_t);
		Vector(const Vector<T> &);
		~Vector();

		size_t getSize() const;
		size_t getCapacity() const;

		T & operator[](int);
		T operator[](int) const;
	
		void resetSize();
		const Vector<T> &operator=(const Vector<T> &);
		void append(const T &);
		void resize(size_t);
private:
		size_t length;
		size_t 	allocSize;
		T *elements;

};

template<class T>
ostream &operator<<(ostream &output, const Vector<T> &v)
{
	size_t i;

	if( v.getSize() == 0 ){
		output << "()";
		return output;
	}

	for(i = 0; i<v.getSize(); i++)
		output<<v[i]<<" ";

	return output;
}

template<class T>
istream &operator>>(istream &input, Vector<T> &v)
{
	T val;
	for(size_t i = 0; i<v.getCapacity(); i++){
		input >> val;
		v[i] = val;
	}
	return input;
}

template <class T> 
Vector<T>::Vector()
{
	length=0;
	allocSize=0;
	elements=NULL;
}

template <class T> 
Vector<T>::Vector(size_t l)
{
	length = 0; 
 	allocSize = l;
	elements = new T[allocSize];
}

template <class T> 
Vector <T>::Vector(const Vector<T>& v)
{
	allocSize=v.allocSize;
	length=v.length;
	elements=new T[allocSize];

	for(size_t i=0;i<v.length;i++)
		elements[i]=v.elements[i];
}

template <class T> 
Vector<T>::~Vector()
{
	delete [] elements;
}

template<class T> 
size_t Vector<T>::getSize() const
{
	return length;
}

template<class T>
size_t Vector<T>::getCapacity() const
{
	return allocSize;
}

template<class T> 
T& Vector<T>::operator[](int i)
{
	if (i<0 || i>=length)
	{
		cerr<<"\nError: subindice "<< i <<" fuera de rango"<<endl;
		exit(1);
	}
	
	return elements[i];
}
		
template<class T> 
T Vector<T>::operator[](int i) const
{
	if (i<0 || i>=length)
	{
		cerr<<"\nError: subindice "<< i <<" fuera de rango"<<endl;
		exit(1);
	}
	
	return elements[i];
}

template<class T> 
void Vector<T>::resetSize()
{
	length=0;
}

template<class T> 
const Vector<T>& Vector<T>::operator=(const Vector<T> &v)
{

	if(this!=&v)
	{
		if(allocSize!=v.allocSize)
		{
			delete[]elements;
			length=v.length;
			allocSize = v.allocSize;
			elements = new T[v.allocSize];
		}
		length = v.length;
		for(size_t i=0;i<length;i++)
			elements[i]=v.elements[i];
	}

	return *this;
}

template<class T> 
void Vector<T>::append(const T &data)
{
	if(allocSize==length)
		resize(CHOP_SIZE);
	
	elements[length]=data;
	length++;
}

template <class T> 
void Vector <T>::resize(size_t n)
{
	T *aux;
	allocSize+=n;
	
	aux=new T[allocSize];
	
	for(size_t i=0;i<length;i++)
		aux[i]=elements[i];
	
	delete[]elements;
	
	elements=aux;
}

#endif
