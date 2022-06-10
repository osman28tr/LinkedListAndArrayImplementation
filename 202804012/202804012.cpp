// 202804012.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include <chrono>
#include <stdlib.h>

struct Node {
	int veri;
	Node* sonraki;
};
struct LinkedList {
	Node* bas;
	void olustur();
	void ekle(int veri, int sira);
	void indisekle(int veri, int sira);
	void sil(int sira);
	void güncelle(int sira, int veri);
	void yazdir();
	void bosalt();
	int sayac;
};

struct ArrayList {
	int* bas;
	void olustur();
	void ekle(int veri, int sira);
	void indisekle(int veri, int sira);
	void guncelle(int veri, int sira);
	void sil(int sira);
	void yazdir();
	void bosalt();
	int sayac;
};

int main()
{
	int iteration = 100;

	LinkedList* ll = new LinkedList();
	ll->olustur();

	for (int i = 0;i < iteration;i++) {
		ll->ekle(i, i);
	}

	cout << endl;

	auto begin1 = std::chrono::high_resolution_clock::now();


	ll->sil(4);

	cout << " 100 elemanli bir listede";

	auto end1 = std::chrono::high_resolution_clock::now();
	auto elapsed1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
	cout << " Baglantili Liste ile gerceklemede silme suresi = > " << elapsed1.count() << " mikro-saniye" << endl;


	ArrayList* al = new ArrayList();
	al->olustur();

	for (int i = 0;i < iteration;i++) {
		al->ekle(i, i);
	}

	cout << endl;

	auto begin2 = std::chrono::high_resolution_clock::now();
	
	al->sil(4);

	cout << endl;
	cout << endl;

	cout << " 100 elemanli bir listede";

	auto end2 = std::chrono::high_resolution_clock::now();
	auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);
	cout << " Dizi ile gerceklemede silme suresi = > " << elapsed2.count() << " mikro-saniye" << endl;
	al->bosalt();
	ll->bosalt();
	cout << "Linked List bosaltildi" << endl;
	cout << "Array List bosaltildi" << endl;
}

void LinkedList::olustur() {
	bas = NULL;
	sayac = 0;
}
void LinkedList::ekle(int veri, int sira) {
	if (bas == 0 && sira == 0) {//basa ekleme
		bas = new Node();
		bas->veri = veri;
		bas->sonraki = NULL;
		return;
	}

	Node* yeni = new Node();
	yeni->veri = veri;
	Node* temp = bas;
	Node* temp2;
	int say = 1;
	while (temp && (say < sira)) {

		temp = temp->sonraki;
		say++;
	}
	if (temp) {
		sayac++;

		temp->sonraki = yeni;
		temp2 = temp;
		yeni->sonraki = temp2->sonraki->sonraki;

	}
	else
	{
		cout << "eklenecek indis gecerli degil";
	}
}
void LinkedList::yazdir() {
	Node* temp = bas;
	while (temp != NULL) {
		cout << temp->veri;
		temp = temp->sonraki;
	}
}
void LinkedList::sil(int sira) {

	Node* temp;
	Node* arka = NULL;
	int say = 1;
	temp = bas;
	if (sira <= 0) {
		cout << "Hatali kayit numarasi";
		return;
	}
	if (sira == 1) {
		bas = temp;
		bas = temp->sonraki;
		delete temp;
		sayac--;
		return;
	}
	if (temp->sonraki == NULL) { //sadece 1 eleman varsa  onu silsin.
		delete temp;
		temp = 0;
		return;
	}
	while ((temp != NULL) && (say < sira)) {
		arka = temp;
		temp = temp->sonraki;
		say++;
	}
	if (say < sira) { //verilen indis çok büyük
		cout << "silinecek kayit bulunamadi";
	}
	else {
		arka->sonraki = temp->sonraki;
		delete temp;
		temp = 0;
		sayac--;
	}
}
void LinkedList::güncelle(int veri, int sira) {
	if (bas == 0) {
		cout << "Linked list is empty";
	}
	if (sira <= 0) {
		cout << "hatali kayit numarasi";
		return;
	}
	Node* temp;

	int say = 1;
	temp = bas;
	while (temp && (say < sira)) {
		say++;
		temp = temp->sonraki;
	}
	if (temp) {
		temp->veri = veri;
	}
	else
		cout << "güncellenecek kayit bulunamadi";
}
void LinkedList::bosalt() {
	Node* temp = bas;
	while (bas) {
		temp = bas;
		bas = bas->sonraki;
		delete temp;
	}
	sayac = 0;
}
void LinkedList::indisekle(int veri, int sira) {
	Node* temp = bas;
	int say = 1;

	if (sira == 0) {
		cout << "hatali sira numarasi girdiniz!";
	}

	if (sira == 1) { //basa ekleme
		Node* yeni = new Node();
		yeni->veri = veri;
		yeni->sonraki = temp;
		bas = yeni;
		return;
	}
	else if (sira == 100) { //sona ekleme
		Node* yeni = new Node();
		yeni->veri = veri;
		while (temp->sonraki)
		{
			temp = temp->sonraki;
		}
		temp->sonraki = yeni;
		return;
	}
	else //araya ekleme
	{
		Node* arka = temp;
		Node* yeni = new Node();
		yeni->veri = veri;
		while (say != sira)
		{
			arka = temp;
			temp = temp->sonraki;
			say++;
		}
		arka->sonraki = yeni;
		yeni->sonraki = temp;
	}
}

void ArrayList::olustur() {
	bas = new int[100];
	sayac = 0;
}
void ArrayList::bosalt() {
	delete[] bas;
	sayac = 0;
}
void ArrayList::yazdir() {
	for (int i = 0; i < sayac; i++)
	{
		cout << *(bas + i);
	}
}
void ArrayList::ekle(int veri, int sira) {
	*(bas + sira) = veri;
	sayac++;
}
void ArrayList::sil(int sira) {
	int say = 1;
	if (sira <= 0) {
		cout << "hatali sira girdiniz!";
		return;
	}

	while (say != sira)
	{
		say++;
	}

	sayac--;
	for (int i = sira - 1; i < sayac; i++)
	{
		*(bas + i) = *(bas + i + 1);
	}
}
void ArrayList::guncelle(int veri, int sira) {
	if (sira <= 0) {
		cout << "hatali kayit numarasi";
		return;
	}

	int say = 1;

	while (say != sira) {
		say++;
	}

	*(bas + say - 1) = veri;


}
void ArrayList::indisekle(int veri, int sira) {
	int* bas2;
	bas2 = bas;
	bas = new int[sayac + 1];

	if (sira == 0) {
		cout << "girdiginiz sira numarasi hatali!";
	}

	for (int i = sayac; i > sira - 2; i--)
	{
		*(bas2 + i + 1) = *(bas2 + i);
	}
	*(bas2 + sira - 1) = veri;
	for (int i = 0; i < sayac + 1; i++)
	{
		cout << *(bas2 + i);
	}
	sayac++;
}
