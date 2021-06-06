#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include "resource.h"

using namespace std;

#define MESA1 6481
#define MESA2 6482
#define MESA3 6483
#define MESA4 6484
#define MESA5 6485
#define MESA6 6486
#define MESA7 6487
#define MESA8 6488
#define MESA9 6489
#define MESAa 6490
#define MESAb 6491
#define MESAc 6492
#define MESAd 6493
#define MESAe 6494
#define MESAf 6495


template <class T> class ButtonList {
	HWND hwnd;
	HWND Static;
	HBITMAP bitbuff;
	T ButtInfo;
	int IDC;
public:
	int Pos;
	ButtonList(int idc) {
		IDC = idc;
	}
	ButtonList() {
		IDC = 0;
	}
	~ButtonList() {
	}
	//Set
	void SetIDC(int idc) {
		this->IDC = idc;
	}
	void SetBitmap(char *BUFF) {
		this->bitbuff = (HBITMAP)LoadImage(NULL, BUFF, IMAGE_BITMAP, 90, 90, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		SendMessage(this->hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)this->bitbuff);
	}
	void SetStaticText(char *BUFF) {
		SetWindowText(this->Static, BUFF);
	}
	void SetButtInfo(T Info) {
		this->ButtInfo = Info;
	}
	//Get
	int GetIDC() {
		return this->IDC;
	}
	HWND GetHWND() {
		return this->hwnd;
	}
	HWND GetStaticHWND() {
		return this->Static;
	}
	T GetButtInfo() {
		return ButtInfo;
	}

	void CrearBoton(int Xpos, int Ypos, int bWidth, int bHeight, DWORD ButtStyles, DWORD StaticStyles, HFONT hFont, HWND Padre, HINSTANCE hIns) {
		this->Pos = Ypos;
		this->hwnd = CreateWindowEx(
			WS_EX_TRANSPARENT,          // Optional window styles.
			"BUTTON",  // Predefined class; Unicode assumed 
			"",      // Button text 
			ButtStyles,//WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE | BS_BITMAP | BS_LEFT | BS_VCENTER,  // Styles 
			Xpos,         // x position 
			Ypos,         // y position 
			bWidth,        // Button width
			bHeight,        // Button height
			Padre,     // Parent window
			(HMENU)this->IDC,       // No menu.
			hIns,
			NULL);      // Pointer not needed.
		this->Static = CreateWindowEx(
			WS_EX_TOPMOST,        // Optional window styles.
			"STATIC",  // Predefined class; Unicode assumed 
			"",      // Button text 
			StaticStyles,//SS_LEFT | WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
			120,         // x position 
			10,         // y position 
			bWidth - 20,        // Button width
			bHeight - 20,        // Button height
			this->hwnd,     // Parent window
			(HMENU)NULL,       // No menu.
			hIns,
			NULL);      // Pointer not needed.
		//HFONT hFont = CreateFontA(10, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(this->hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(this->Static, WM_SETFONT, (WPARAM)hFont, TRUE);
	}

};

//Clases para lista ligada
template <class Data> class ListaLigada;
template <class Data1> class Nodo {
public:
	Nodo *nxt;
	Nodo *prv;

	Data1 Datos;

	Nodo(Data1 Dat) {
		this->Datos = Dat;
		nxt = 0;
		prv = 0;
	}
	Nodo() {
		nxt = 0;
		prv = 0;
	}

	//template<class Data> friend class ListaLigada;
};
//Todos los objetos tipo "Lista Ligada" no requieren una funcion de eliminar devido a que el destructor de la 
//                  clase se encarga de desaherce de la lista ligada que contiene
template <class Data> class ListaLigada {
public:
	Nodo<Data> *head;
	Nodo<Data> *tail;

	ListaLigada() {
		head = 0;
		tail = 0;
	}
	void DeleteList() {
		Nodo<Data> *aux;
		while (this->head != 0) {
			aux = this->head;
			this->head = this->head->nxt;
			delete aux;
		}
		this->head = 0;
		this->tail = 0;
	}
	~ListaLigada() {
		this->DeleteList();
	}

	bool InsertAheadOf(Nodo<Data> *Node, Nodo<Data> *Insert) {
		try {
			if (Node == 0 || Insert == 0) {
				throw (int)1;
			}
			else {
				if (Node->prv == 0) {
					this->head = Insert;
					Insert->prv = 0;
					Node->prv = Insert;
					Insert->nxt = Node;
				}
				else {
					Insert->nxt = Node;
					Insert->prv = Node->prv;
					Node->prv->nxt = Insert;
					Node->prv = Insert;
				}
			}
			return true;
		}
		catch (int PuntroNulo) {
			return false;
		}
	}
	bool InsertBehindOf(Nodo<Data> *Node, Nodo<Data> *Insert) {
		try {
			if (Node == 0 || Insert == 0) {
				throw (int)1;
			}
			else {
				if (Node->nxt == 0) {
					this->tail = Insert;
					Insert->nxt = 0;
					Node->nxt = Insert;
					Insert->prv = Node;
				}
				else {
					Insert->prv = Node;
					Insert->nxt = Node->nxt;
					Node->nxt->prv = Insert;
					Node->nxt = Insert;
				}
			}
			return true;
		}
		catch (int PuntroNulo) {
			return false;
		}
	}
	bool XChange(Nodo<Data> *Node1, Nodo<Data> *Node2) {
		try {
			if (Node1 == 0 || Node2 == 0) {
				throw (int)1;
			}
			Data Aux = Node1->Datos;
			Node1->Datos = Node2->Datos;
			Node2->Datos = Aux;
			return true;
		}
		catch (int PuntroNulo) {
			return false;
		}
	}
	bool Disconect(Nodo<Data> *Disconect) {
		try {
			if (Disconect == 0) {
				throw (int)1;
			}

			if (Disconect == this->head) {
				if (Disconect == this->tail) {
					this->tail = 0;
					this->head = 0;
					//delete Remove;
				}
				else {
					this->head = this->head->nxt;
					this->head->prv = 0;
					//delete Remove;
				}
			}
			else if (Disconect == this->tail) {
				this->tail = this->tail->prv;
				this->tail->nxt = 0;
				//delete Remove;
			}
			else {
				Disconect->nxt->prv = Disconect->prv;
				Disconect->prv->nxt = Disconect->nxt;
				//delete Remove;
			}
			//delete Disconect;
			Disconect->nxt = 0;
			Disconect->prv = 0;
			return true;
		}
		catch (int PunteroNulo) {
			return false;
		}
	};
	bool AddLast(Nodo<Data> *New) {
		try {
			if (New == 0) {
				throw (int)1;
			}
			Nodo<Data> *aux = New;
			aux->nxt = 0;
			aux->prv = 0;
			if (head == 0) {
				this->head = aux;
				this->tail = aux;
			}
			else {
				if (head->nxt == 0) {
					this->head->nxt = aux;
					this->tail = aux;
					this->tail->prv = this->head;
				}
				else {
					aux->prv = this->tail;
					this->tail->nxt = aux;
					this->tail = aux;
				}
			}
			return true;
		}
		catch (int PuntroNulo) {
			return false;
		}
	}
	bool Remove(Nodo<Data> *Remove) {
		try {
			if (Remove == 0) {
				throw (int)1;
			}

			if (Remove == this->head) {
				if (Remove == this->tail) {
					this->tail = 0;
					this->head = 0;
					//delete Remove;
				}
				else {
					this->head = this->head->nxt;
					this->head->prv = 0;
					//delete Remove;
				}
			}
			else if (Remove == this->tail) {
				this->tail = this->tail->prv;
				this->tail->nxt = 0;
				//delete Remove;
			}
			else {
				Remove->nxt->prv = Remove->prv;
				Remove->prv->nxt = Remove->nxt;
				//delete Remove;
			}
			delete Remove;
			return true;
		}
		catch (int PunteroNulo) {
			return false;
		}
	}
	bool AddFirst(Nodo<Data> *New) {
		try {
			if (New == 0) {
				throw (int)1;
			}
			Nodo<Data> *aux = New;
			aux->nxt = 0;
			aux->prv = 0;
			if (head == 0) {
				this->head = aux;
				this->tail = aux;
			}
			else {
				if (tail->prv == 0) {
					this->tail->prv = aux;
					this->head = aux;
					this->head->nxt = this->tail;
				}
				else {
					aux->nxt = this->head;
					this->head->prv = aux;
					this->head = aux;
				}
			}
			return true;
		}
		catch (int PuntroNulo) {
			return false;
		}
	}
	int Count() {
		Nodo<Data> *Aux;
		int Sum = 0;
		Aux = this->head;
		while (Aux != 0) {
			Sum++;
			Aux = Aux->nxt;
		}
		return Sum;
	}

	void CopyList(ListaLigada<Data>* Receptor) {
		int C = this->Count();
		for (int I = 0; I < C; I++) {
			Nodo<Data> * NewNode = new Nodo<Data>;
			NewNode->Datos = this->operator[](I)->Datos;
			Receptor->AddLast(NewNode);
		}
	}
	void Copy(Nodo<Data>* Copy) {
		Nodo<Data> * NewNode = new Nodo<Data>;
		NewNode->Datos = Copy->Datos;
		this->AddLast(NewNode);
	}

	void ReadList(const char In[]) {
		ifstream in(In, ios::binary | ios::in);
		if (in.is_open()) {
			in.seekg(0, in.end);
			std::streamoff endd = in.tellg();
			in.seekg(0, in.beg);
			while (in.tellg() < endd) {
				Nodo<Data>* aux = new Nodo<Data>;
				in.read((char*)&aux->Datos, sizeof(Data));
				this->AddLast(aux);
			}
		}
		in.close();
	}
	void WriteList(const char Out[]) {
		ofstream out(Out, ios::binary | ios::out | ios::trunc);
		int J = this->Count();
		Nodo<Data>* aux = this->head;
		for (int I = 0; I < J; I++,aux = aux->nxt) {
			out.write((char*)&aux->Datos, sizeof(Data));
		}
		out.close();
	}

	Nodo<Data>* operator [](int I) {
		Nodo<Data>* aux = this->head;
		for (int J = 0; J < I; J++) {
			if (aux != 0) {
				aux = aux->nxt;
			}
			else {
				return 0;
			}
		}
		return aux;
	}

};
 

enum comida { POSTRE, BEBIDA , DESAYUNO , COMIDA, CENA };
enum estado { LIBRE, OCUPADA, EN_USO};
enum metodo_de_pago{EFECTIVO,TARJETA,PAYPAL,CUPON};

class Comienda;
struct Stuff;

class Alimento {
	
	int ID;
	static int LastID;
	char Nombre[100];

	comida Categoria;

	//variables para guardar la imagen
	HBITMAP BitBuff;
	char buffer[300];

	float Precio = 0;

	friend Stuff;
	friend Comienda;

public:

	Alimento() {
		ID = LastID;
		LastID++;
	}

	Alimento(Alimento *aux){
		memset(this->Nombre, NULL, sizeof(this->Nombre));
		strcpy_s(this->Nombre,sizeof(this->Nombre),aux->Nombre);
		this->Precio = aux->Precio;
		this->ID = aux->ID;
	}

	~Alimento() {
	}

	bool CmpNme(char N[]) {
		// true == Son identicos, false == No lo son
		int I;
		for (I = 0; N[I] != 0; I++);
		int J;
		for (J = 0; this->Nombre[J] != 0; J++);
		if (J != I) {
			return false;
		}
		else {
			for (I = 0; N[I] != 0; I++) {
				if (N[I] == this->Nombre[I]) {
					continue;
				}
				return false;
			}
			return true;
		}
	}

	//Set
	void SetPrice(float N) {
		this->Precio = N;
	}
	void SetName(char cadena[]) {
		int I;
		for (I = 0; cadena[I] != 0; I++);
		if (!(I + 1 > sizeof(this->Nombre))) {
			for (int J = 0; J < I; J++) {
				this->Nombre[J] = cadena[J];
			}
		}
	}
	void SetBuff(char Direccion[]) {
		int I;
		for (I = 0; Direccion[I] != 0; I++);
		if (!(I + 1 > sizeof(this->buffer))) {
			for (I = 0; Direccion[I] != 0; I++) {
				buffer[I] = Direccion[I];
			}
		}
	}
	void SetCategory(comida C) {
		this->Categoria = C;
	}

	//Get
	int GetID() {
		return this->ID;
	}
	float GetPrice() {
		return this->Precio;
	}
	bool GetName(char *N, int Size) {
		int I;
		for (I = 0; Nombre[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I + 1; J++) {
			N[J] = this->Nombre[J];
		}
		return true;
	}
	bool GetBuff(char *N, int Size) {
		int I;
		for (I = 0; buffer[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I+1; J++) {
			N[J] = this->buffer[J];
		}
		return true;
	}
	comida GetCategory() {
		return this->Categoria;
	}
};
int Alimento::LastID = 0;
class Empleado {

	char Nombre[100];
	char Correo[150];
	char Telefono[12];

	char Usuario[50];
	char Contraseña[50];

	//variables para guardar la imagen
	HBITMAP BitBuff;
	char buffer[300];

public:
	int Level;
	Empleado *izq;
	Empleado *der;
	

	Empleado() {
	}
	
	~Empleado() {
	}
	bool UserCmp(char user[]) {
		// true == Son identicos, false == No lo son
		int I;
		for (I = 0; user[I] != 0; I++);
		int J;
		for (J = 0; this->Usuario[J] != 0; J++);
		if (J != I) {
			return false;
		}
		else {
			for (I = 0; user[I] != 0; I++) {
				if (user[I] == this->Usuario[I]) {
					continue;
				}
				return false;
			}
			return true;
		}
	}
	bool PassCmp(char pass[]) {
		int I;
		for (I = 0; pass[I] != 0; I++);
		int J;
		for (J = 0; this->Contraseña[J] != 0; J++);
		if (J != I) {
			return false;
		}
		else {
			for (I = 0; pass[I] != 0; I++) {
				if (pass[I] == this->Contraseña[I]) {
					continue;
				}
				return false;
			}
			return true;
		}
	}

	//Set
	void SetName(char cadena[]) {
		memset(this->Nombre, NULL, sizeof(this->Nombre));
		int I;
		for (I = 0; cadena[I] != 0; I++);
		if (!(I + 1 > sizeof(this->Nombre))) {
			for (int J = 0; J < I; J++) {
				this->Nombre[J] = cadena[J];
			}
		}
	}
	void SetMail(char cadena[]) {
		memset(this->Correo, NULL, sizeof(this->Correo));
		int I;
		for (I = 0; cadena[I] != 0; I++);
		if (!(I + 1 > sizeof(this->Correo))) {
			for (int J = 0; J < I; J++) {
				this->Correo[J] = cadena[J];
			}
		}
		
	}
	bool SetPhon(char cadena[]) {
		memset(this->Telefono, NULL, sizeof(this->Telefono));
		try {
			int I;
			for (I = 0; cadena[I] != 0; I++);
			if (I + 1 > 12) {
				throw (char)'F';
			}
			else if (strlen(cadena) < 8) {
				throw (int)1;
			}
			for (int J = 0; J < I; J++) {
				this->Telefono[J] = cadena[J];
			}
			return true;
		}
		catch (char Cadena_Demaciado_Larga) {
			return false;
		}
		catch (int Cadena_Muy_Corta) {
			return false;
		}
	}
	void SetUser(char cadena[]) {
		memset(this->Usuario, NULL, sizeof(this->Usuario));
		int I;
		for (I = 0; cadena[I] != 0; I++);
		if (!(I + 1 > sizeof(this->Usuario))) {
			for (int J = 0; J < I; J++) {
				this->Usuario[J] = cadena[J];
			}
		}
	}
	void SetPass(char cadena[]) {
		memset(this->Contraseña, NULL, sizeof(this->Contraseña));
		int I;
		for (I = 0; cadena[I] != 0; I++);
		if (!(I + 1 > sizeof(this->Contraseña))) {
			for (int J = 0; J < I; J++) {
				this->Contraseña[J] = cadena[J];
			}
		}
	}
	void SetBuff(char cadena[]) {
		memset(this->buffer, NULL, sizeof(this->buffer));
		int I;
		for (I = 0; cadena[I] != 0; I++);
		if (!(I + 1 > sizeof(this->buffer))) {
			for (int J = 0; J < I; J++) {
				this->buffer[J] = cadena[J];
			}
		}
	}

	//Get
	bool GetName(char *N, int Size) {
		int I;
		for (I = 0; Nombre[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I + 1; J++) {
			N[J] = this->Nombre[J];
		}
		return true;
	}
	bool GetMail(char *N, int Size) {
		int I;
		for (I = 0; Correo[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I + 1; J++) {
			N[J] = this->Correo[J];
		}
		return true;
	}
	bool GetPhon(char *N, int Size) {
		int I;
		for (I = 0; Telefono[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I + 1; J++) {
			N[J] = this->Telefono[J];
		}
		return true;
	}
	bool GetUser(char *N, int Size) {
		int I;
		for (I = 0; Usuario[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I + 1; J++) {
			N[J] = this->Usuario[J];
		}
		return true;
	}
	bool GetPass(char *N, int Size) {
		int I;
		for (I = 0; Contraseña[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I + 1; J++) {
			N[J] = this->Contraseña[J];
		}
		return true;
	}
	bool GetBuff(char *N, int Size) {
		int I;
		for (I = 0; buffer[I] != 0; I++);
		if (I + 1 > Size) {
			return false;
		}
		for (int J = 0; J < I + 1; J++) {
			N[J] = this->buffer[J];
		}
		return true;
	}

	friend void EscribirEnArchivoBinEmpleados(Empleado* Raiz);
};

class Mesa {
	//Parte de "Comienda", las mesas son objetos que no desaparecen a lo largo del programa
	HWND hwnd;
	POINT ButtonCoord;
	unsigned int IDC;

	HBITMAP State;

	char Responsable[50];

	estado Estado;
	int TableNum;

public:

	Mesa(int N) {
		TableNum = N;
		switch (N) {
		case 1:
		{
			IDC = MESA1;
			ButtonCoord.x = 25;
			ButtonCoord.y = 0;
		}
		break;
		case 2:
		{
			IDC = MESA2;
			ButtonCoord.x = 100;
			ButtonCoord.y = 0;
		}
		break;
		case 3:
		{
			IDC = MESA3;
			ButtonCoord.x = 175;
			ButtonCoord.y = 0;
		}
		break;
		case 4:
		{
			IDC = MESA4;
			ButtonCoord.x = 30;
			ButtonCoord.y = 74;
		}
		break;
		case 5:
		{
			IDC = MESA5;
			ButtonCoord.x = 110;
			ButtonCoord.y = 74;
		}
		break;
		case 6:
		{
			IDC = MESA6;
			ButtonCoord.x = 30;
			ButtonCoord.y = 147;
		}
		break;
		case 7:
		{
			IDC = MESA7;
			ButtonCoord.x = 110;
			ButtonCoord.y = 147;
		}
		break;
		case 8:
		{
			IDC = MESA8;
			ButtonCoord.x = 195;
			ButtonCoord.y = 147;
		}
		break;
		case 9:
		{
			IDC = MESA9;
			ButtonCoord.x = 30;
			ButtonCoord.y = 223;
		}
		break;
		case 10:
		{
			IDC = MESAa;
			ButtonCoord.x = 110;
			ButtonCoord.y = 223;
		}
		break;
		case 11:
		{
			IDC = MESAb;
			ButtonCoord.x = 195;
			ButtonCoord.y = 223;
		}
		break;
		case 12:
		{
			IDC = MESAc;
			ButtonCoord.x = 76;
			ButtonCoord.y = 302;
		}
		break;
		case 13:
		{
			IDC = MESAd;
			ButtonCoord.x = 146;
			ButtonCoord.y = 302;
		}
		break;
		case 14:
		{
			IDC = MESAe;
			ButtonCoord.x = 220;
			ButtonCoord.y = 302;
		}
		break;
		case 15:
		{
			IDC = MESAf;
			ButtonCoord.x = 290;
			ButtonCoord.y = 302;
		}
		break;
		}
	}

	void SetState(estado E) {
		this->Estado = E;
		RECT rect;
		GetWindowRect(this->hwnd, &rect);

		switch (E) {
		case LIBRE:
		{
			memset(this->Responsable, NULL, sizeof(this->Responsable));
			if (this->TableNum > 3 && this->TableNum < 12) {
				this->State = (HBITMAP)LoadImage(NULL, "Tables\\TableA0.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			}
			else {
				this->State = (HBITMAP)LoadImage(NULL, "Tables\\TableB0.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			}
		}
		break;
		case OCUPADA:
		{
			if (this->TableNum > 3 && this->TableNum < 12) {
				this->State = (HBITMAP)LoadImage(NULL, "Tables\\TableA1.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			}
			else {
				this->State = (HBITMAP)LoadImage(NULL, "Tables\\TableB1.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			}
		}
		break;
		case EN_USO:
		{
			if (this->TableNum > 3 && this->TableNum < 12) {
				this->State = (HBITMAP)LoadImage(NULL, "Tables\\TableA2.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			}
			else {
				this->State = (HBITMAP)LoadImage(NULL, "Tables\\TableB2.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			}
		}
		break;
		}

		SendMessage(this->hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)this->State);
	}

	estado GetState() {
		return this->Estado;
	}

	HWND GetHWND() {
		return this->hwnd;
	}

	void CreateButton(HWND Padre, HINSTANCE hIns, estado E) {
		if (this->TableNum > 3 && this->TableNum < 12) {
			this->hwnd = CreateWindow(
				"BUTTON",  // Predefined class; Unicode assumed 
				"",      // Button text 
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE | BS_BITMAP | BS_CENTER | BS_VCENTER,  // Styles 
				ButtonCoord.x,         // x position 
				ButtonCoord.y,         // y position 
				60,        // Button width
				60,        // Button height
				Padre,     // Parent window
				(HMENU)this->IDC,       // No menu.
				hIns,
				NULL);      // Pointer not needed.
		}
		else {
			this->hwnd = CreateWindow(
				"BUTTON",  // Predefined class; Unicode assumed 
				"",      // Button text 
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE | BS_BITMAP | BS_CENTER | BS_VCENTER,  // Styles 
				ButtonCoord.x,         // x position 
				ButtonCoord.y,         // y position 
				50,        // Button width
				50,        // Button height
				Padre,     // Parent window
				(HMENU)this->IDC,       // No menu.
				hIns,
				NULL);      // Pointer not needed.
		}
		if (E == OCUPADA || E == EN_USO) {
			EnableWindow(this->hwnd,FALSE);
		}
		SetState(E);
	}

	void SetWorker(Empleado *Worker) {
		if (Worker != 0) {
			memset(this->Responsable, NULL, sizeof(this->Responsable));
			Worker->GetUser(this->Responsable, sizeof(this->Responsable));
			this->SetState(OCUPADA);
		}
	}

	void GetInChargeUser(char* N) {
	
		strcpy_s(N,sizeof(this->Responsable),this->Responsable);
		
	}

	int GetTableNum() {
		return TableNum;
	}
};
class Comienda {
	int Folio;
	static int LastFolio;
	// 0 .5 .10 .15 .20 
	float Propina;
	tm Fecha;
	int Table;
	int Clients;
	metodo_de_pago pago;
	char Employee[50];
	friend Stuff;
	friend void EmployeeQuickSort(ListaLigada<Comienda>* Orders, Nodo<Comienda>* l, Nodo<Comienda>*h);
	friend void EmployeeFilter(ListaLigada<Comienda>* Orders, char User[]);
public:
	//ListaLigada<Comensal> Clientes;

	Comienda() {
		Table = 0;
		pago = EFECTIVO;
		Clients = 0;
		Propina = 0.0;
		time_t t = time(0);
		localtime_s(&Fecha, &t);
		Folio = LastFolio;
		LastFolio++;
	}

	void SetTip(float TipPercentage) {
		Propina = TipPercentage;
	}
	void SetTable(Mesa *T) {
		this->Table = T->GetTableNum();
		T->GetInChargeUser(this->Employee);
	}
	void SetClientNum(int I) {
		this->Clients = I;
	}
	void SetPayment(metodo_de_pago P) {
		this->pago = P;
	}

	float GetTip() {
		return Propina;
	}
	int GetTableNumber() {
		return this->Table;
	}
	int GetFolio() {
		return this->Folio;
	}
	int GetClientNum() {
		return this->Clients;
	}
	tm* GetDate() {
		return &this->Fecha;
	}
	metodo_de_pago GetPayment() {
		return this->pago;
	}

	
};
int Comienda::LastFolio = 0;
struct Stuff {
	int Folio;
	int ClientNum;
	int FoodID;
	float FoodPrice;
};
//Manejo del Arbol Binario
Empleado* FindFreeParent(Empleado* Raiz) {
	//Reparar esto si es que se implementa el ilbanado
	if (Raiz != 0) {
		Empleado* auxizq = FindFreeParent(Raiz->izq);
		Empleado* auxder = FindFreeParent(Raiz->der);
		if (auxizq == 0 || auxder == 0) {
			return Raiz;
		}
		else if(auxizq->Level <= auxder->Level){
			return auxizq;
		}
		else {
			return auxder;
		}
	}
	return 0;
}
Empleado* FindParent(Empleado* Raiz, Empleado* Child) {
	if (Raiz != 0 && Child != 0) {
		if (Raiz->izq == Child || Raiz->der == Child) {
			return Raiz;
		}
		else {
			Empleado* auxizq = FindParent(Raiz->izq, Child);
			Empleado* auxder = FindParent(Raiz->der, Child);
			if (auxizq != 0) {
				return auxizq;
			}
			else if (auxder != 0) {
				return auxder;
			}
		}
	}
	return 0;
}
Empleado* FindLeaf(Empleado* Raiz) {
	if (Raiz != 0) {
		if (Raiz->izq != 0) {
			return FindLeaf(Raiz->izq);
		}
		else if (Raiz->der != 0){
			return FindLeaf(Raiz->der);
		}
		else {
			return Raiz;
		}
	}
	return 0;
}
void AddLast(Empleado** Raiz, Empleado *Add) {
	if (*Raiz == 0) {
		*Raiz = Add;
	}
	else {
		Empleado* Parent = FindFreeParent(*Raiz);
		if (Parent->izq == 0) {
			Parent->izq = Add;
		}
		else {
			Parent->der = Add;
		}
		Add->Level = Parent->Level + 1;
	}
};
void Delete(Empleado* Raiz, Empleado* Remove) {
	if (Remove != 0) {
		Empleado *Parent = FindParent(Raiz, Remove);
		if (Remove->der == 0 && Remove->izq == 0) {
			//Caso si es hoja
			if (Parent != 0) {
				if (Parent->izq == Remove) {
					Parent->izq = 0;
				}
				else {
					Parent->der = 0;
				}
			}
		}
		else if (Parent != 0 && Remove->der == 0 || Remove->izq == 0) {
			
				if (Remove->izq == 0) {
					//Caso si está UNICAMENTE conectado por la izquierda
					 
						if (Parent->izq == Remove) {
							Parent->izq = Remove->izq;
						}
						else {
							Parent->der = Remove->izq;
						}
					

				}
				else {
					//Caso si está UNICAMENTE conectado por la derecha
					
						if (Parent->der == Remove) {
							Parent->der = Remove->der;
						}
						else {
							Parent->izq = Remove->der;
						}
					
				}
			}
			else {
				//Caso si está conectado por ambos lados
				Empleado* aux = FindLeaf(Raiz);
				char BUFF[5000] = { NULL };
				aux->GetName(BUFF, sizeof(BUFF));
				Remove->SetName(BUFF);
				memset(BUFF, NULL, strlen(BUFF));

				aux->GetMail(BUFF, sizeof(BUFF));
				Remove->SetMail(BUFF);
				memset(BUFF, NULL, strlen(BUFF));

				aux->GetPhon(BUFF, sizeof(BUFF));
				Remove->SetPhon(BUFF);
				memset(BUFF, NULL, strlen(BUFF));

				aux->GetUser(BUFF, sizeof(BUFF));
				Remove->SetUser(BUFF);
				memset(BUFF, NULL, strlen(BUFF));

				aux->GetPass(BUFF, sizeof(BUFF));
				Remove->SetPass(BUFF);
				memset(BUFF, NULL, strlen(BUFF));

				aux->GetBuff(BUFF, sizeof(BUFF));
				Remove->SetBuff(BUFF);
				memset(BUFF, NULL, strlen(BUFF));

				Remove = aux;
			}
		
		delete Remove;
	}
}
void Talar(Empleado* Raiz) {
	if (Raiz != 0) {
		Talar(Raiz->izq);
		Talar(Raiz->der);
		//Aquí escribimos los datos del contacto en el archivo antes de eliminarlo
		delete Raiz;
	}
}
int CountEmple(Empleado *Raiz) {
	if (Raiz != 0) {
		int izqaux = CountEmple(Raiz->izq);
		int deraux = CountEmple(Raiz->der);
		return (izqaux + deraux + 1);
	}
	return 0;
}
//void Equilibrar(Empleado **Raiz) {}

Empleado* SearchByUser(Empleado* Raiz, char User[]) {
	if (Raiz != 0 && User[0] != 0) {
		if (Raiz->UserCmp(User)) {
			return Raiz;
		}
		else {
			Empleado* auxizq = SearchByUser(Raiz->izq, User);
			Empleado* auxder = SearchByUser(Raiz->der, User);
			if (auxizq != 0) {
				return auxizq;
			}
			else if (auxder != 0) {
				return auxder;
			}
		}
	}
	return 0;
}
Nodo<Alimento>* Search(ListaLigada<Alimento> *Raiz, char Nombre[]) {
	Nodo<Alimento>* Aux;
	Aux = Raiz->head;
	while (Aux != 0) {
		if (Aux->Datos.CmpNme(Nombre)) {
			return Aux;
		}
		Aux = Aux->nxt;
	}
	return 0;
}
Nodo<Alimento>* SearchFoodByID(ListaLigada<Alimento> *Raiz, int ID) {
	Nodo<Alimento>* Aux;
	Aux = Raiz->head;
	while (Aux != 0) {
		if (Aux->Datos.GetID() == ID) {
			return Aux;
		}
		Aux = Aux->nxt;
	}
	return 0;
}
Nodo<Comienda>* SearchOrderByTable(ListaLigada<Comienda>* Orders, Mesa*Table) {
	if (Orders != 0 && Table != 0) {
		Nodo<Comienda>* aux = Orders->head;
		while (aux != 0) {
			if (aux->Datos.GetTableNumber() == Table->GetTableNum()) {
				return aux;
			}
			aux = aux->nxt;
		}
	}
	return 0;
}
Nodo<Comienda>* SearchOrderByFolio(ListaLigada<Comienda>* Orders, int Fol) {
	if (Orders != 0) {
		Nodo<Comienda>* aux = Orders->head;
		while (aux != 0) {
			if (aux->Datos.GetFolio() == Fol) {
				return aux;
			}
			aux = aux->nxt;
		}
	}
	return 0;
}
Nodo<Stuff>* SearchStuffByFolio(ListaLigada<Stuff>* Things, int Fol) {
	if (Things != 0) {
		Nodo<Stuff>* aux = Things->head;
		while (aux != 0) {
			if (aux->Datos.Folio == Fol) {
				return aux;
			}
			aux = aux->nxt;
		}
	}
	return 0;
}

void OrderXChange(int Folio,ListaLigada<Comienda>* Giver, ListaLigada<Stuff>* GiverStuff, ListaLigada<Comienda>* Receptor, ListaLigada<Stuff>* ReceptorStuff) {
	Nodo<Comienda> *Disconected = SearchOrderByFolio(Giver, Folio);
	Giver->Disconect(Disconected);
	Receptor->AddFirst(Disconected);
	bool Out = true;
	while (Out) {
		Nodo<Stuff> *DiStuff = SearchStuffByFolio(GiverStuff, Folio);
		if (DiStuff == 0) {
			Out = false;
		}
		else {
			GiverStuff->Disconect(DiStuff);
			ReceptorStuff->AddFirst(DiStuff);
		}
	}
}

//Raices de las estructuras de nodos
Empleado *Empleados = 0;
ListaLigada<Alimento> Alimentos;
ListaLigada<Comienda> Ordenes; ListaLigada<Stuff> OrdStuff;
ListaLigada<Comienda> Pendientes; ListaLigada<Stuff> PendStuff;
ListaLigada<Comienda> Historial; ListaLigada<Stuff> HistStuff;
ListaLigada<Comienda> Filtered;

Empleado* LoggedInUser = 0;

//Variables
	//Para el Admin
Empleado *Admin = new Empleado;
char AdminUser[50] = { NULL };
char AdminPass[50] = { NULL };

bool DateCmp(tm* Date1,tm* Date2) {
	//false = is older or equal  true = is newer
	if (Date1->tm_year >= Date2->tm_year) {
		if (Date1->tm_yday >= Date2->tm_yday) {
			if (Date1->tm_hour >= Date2->tm_hour) {
				if(Date1->tm_min >= Date2->tm_min){
					if (Date1->tm_sec > Date2->tm_sec) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
//Ordenamiento de Comiendas
void DateInsertSort(ListaLigada<Comienda>* Orders) {
	ListaLigada<Comienda> Sorted;
	Nodo<Comienda>* Curr = Orders->head;
	while(Curr != 0){
		Nodo<Comienda>* next = Curr->nxt;
		Orders->Disconect(Curr);
		for (int I = 0; I < Sorted.Count(); I++) {
			if (DateCmp(Curr->Datos.GetDate(), Sorted[I]->Datos.GetDate())) {
				Sorted.InsertAheadOf(Sorted[I], Curr);
				break;
			}
		}
		if (Curr->nxt == 0 && Curr->prv == 0) {
			Sorted.AddLast(Curr);
		}
		Curr = next;
	}
	Sorted.CopyList(Orders);
}

/* A recursive implementation
of quicksort for linked list */
void EmployeeQuickSort(ListaLigada<Comienda>* Orders,Nodo<Comienda>* l, Nodo<Comienda>*h)
{
	if (h != NULL && l != h && l != h->nxt)
	{
		// set pivot as h element  
		Nodo<Comienda>* x = h;

		// similar to i = l-1 for array implementation  
		Nodo<Comienda>*i = l->prv;

		// Similar to "for (int j = l; j <= h- 1; j++)"  
		for (Nodo<Comienda>*j = l; j != h; j = j->nxt)
		{
			if (strcmp(j->Datos.Employee, x->Datos.Employee) <= 0)
			{
				// Similar to i++ for array  
				i = (i == NULL) ? l : i->nxt;

				Orders->XChange(i, j);
			}
		}
		i = (i == NULL) ? l : i->nxt; // Similar to i++  
		Orders->XChange(i, h);

		EmployeeQuickSort(Orders,l, i->prv);
		EmployeeQuickSort(Orders, i->nxt, h);
	}
}

void EmployeeFilter(ListaLigada<Comienda>* Orders, char User[]) {
	EmployeeQuickSort(Orders,Orders->head,Orders->tail);
	ListaLigada<Comienda> Sorted;
	int C = Orders->Count();
	bool found = false;
	for (int I = 0; I < C; I++) {
		if (strcmp(Orders->operator[](I)->Datos.Employee, User) == 0) {
			Sorted.Copy(Orders->operator[](I));
			found = true;
		}
		else if(found) {
			break;
		}
	}
	Orders->DeleteList();
	Sorted.CopyList(Orders);
};
void DateFilter(ListaLigada<Comienda>* Orders, char Range1[], char Range2[]) {
	DateInsertSort(Orders);
	ListaLigada<Comienda> Sorted;
	int C = Orders->Count();
	bool found = false;
	for (int I = 0; I < C; I++) {
		tm* Date = Orders->operator[](I)->Datos.GetDate();
		char AUX[10] = { NULL };
		char DIR[50] = { NULL };
		if (Date->tm_mday < 10) {
			strcat_s(DIR, "0");
		}
		_itoa_s(Date->tm_mday, AUX, 10);
		strcat_s(DIR, AUX);
		strcat_s(DIR, "/");
		memset(AUX, NULL, strlen(AUX));
		if (Date->tm_mon < 9) {
			strcat_s(DIR, "0");
		}
		_itoa_s(Date->tm_mon + 1, AUX, 10);
		strcat_s(DIR, AUX);
		strcat_s(DIR, "/");
		memset(AUX, NULL, strlen(AUX));
		_itoa_s(Date->tm_year + 1900, AUX, 10);
		strcat_s(DIR, AUX);
		if (strcmp(DIR, Range1) >= 0 && strcmp(DIR, Range2) <= 0) {
			Sorted.Copy(Orders->operator[](I));
			found = true;
		}
		else if (found) {
			break;
		}
	}
	Orders->DeleteList();
	Sorted.CopyList(Orders);
}

//Validaciones
bool ValPhon(char num[]) {
	if ((strlen(num) < 8)) {
		/*cin.clear();
		system("CLS");
		Error();
		gotoxy(16, 3);
		cout << "Error: La cadena de caracteres que usted ingreso es demasiado";
		gotoxy(22, 4);
		cout << " corta.";
		gotoxy(0, 9);
		system("PAUSE");
		gotoxy(0, 0);*/
		return false;
	}
	return true;
}
bool ValName(char nme[], int cap) {
	if (strlen(nme) > cap) {
		return false;
	}
	for (int I = 0; I < strlen(nme); I++) {
		if (!(isalpha(nme[I]) || isspace(nme[I]))) {
			return false;
		}
	}
	return true;
}
bool ValMail(char mail[]) {
	try {
		int J, PosA = 6480;
		char Arr = '@', Pnt = '.', C = 'c', O = 'o', M = 'm', E = 'e', D = 'd', U = 'u';
		/*if (strlen(mail) > 45) {
			return false;
		}*/
		if (ispunct(mail[0])) {
			throw (char) 'F';
		}
		if ((mail[strlen(mail) - 4] != Pnt || mail[strlen(mail) - 3] != C || mail[strlen(mail) - 2] != O || mail[strlen(mail) - 1] != M) && (mail[strlen(mail) - 4] != Pnt || mail[strlen(mail) - 3] != E || mail[strlen(mail) - 2] != D || mail[strlen(mail) - 1] != U) && (mail[strlen(mail) - 7] != Pnt || mail[strlen(mail) - 6] != C || mail[strlen(mail) - 5] != O || mail[strlen(mail) - 4] != M || mail[strlen(mail) - 3] != Pnt)) {
			throw (int)3;
		}
		for (J = 0; J < strlen(mail); J++) {
			if (isalnum(mail[J]) || ispunct(mail[J])) {
				if (mail[J] == Arr) {
					if (PosA == 6480) {
						PosA = J;
					}
					else {
						throw (bool)true;
					}
				}
				if (mail[J] == Pnt && mail[J - 1] == Pnt) {
					throw (double) 222.123;
				}
			}
			else {
				throw (short)1;
			}
		}
		if (PosA == 6480) {
			throw (bool)false;
		}
		if (isalnum(mail[PosA + 1]) && isalnum(mail[PosA - 1])) {
			return true;
		}
		throw (float) 12.15;
	}
	catch (bool Arroba) {
		try {
			if (!Arroba) {
				throw (int)9;
			}
			throw (char) 'G';
		}
		catch (int Sin_Arroba) {
			return false;
		}
		catch (char Multi_Arroba) {
			return false;
		}
	}
	catch (float Correo_Invalido) {
		return false;
	}
	catch (char Empieza_Con_Caracter_Invalido) {
		return false;
	}
	catch (int Terminacion_Invalida) {
		return false;
	}
	catch (double Punto_Al_Lado_De_Otro_Punto) {
		return false;
	}
	catch (short Caracter_Invalido) {
		return false;
	}
}
bool ValUser(Empleado *Raiz, char user[]){
	//true == hay coincidencia, false == no hay coincidencias (Por lo tanto el usuario no existe registrado)
	if (Raiz != 0) {
		if (strcmp(user, AdminUser) != 0) {
			return (ValUser(Raiz->izq, user) || ValUser(Raiz->der, user) || Raiz->UserCmp(user));
		}
		return true;
	}
	return false;
}
bool ValPass(char pass[],char confim[]) {
	if (strlen(pass) == strlen(confim)) {
		if (strcmp(pass, confim) == 0) {
			return true;
		}
	}
	return false;
}

Empleado* LogIn(Empleado* Raiz, char User[],char Pass[]) {
	
	if ((strcmp(User, AdminUser) == 0) && (strcmp(Pass, AdminPass) == 0)) {
		return Admin;
	}
	if (Raiz != 0) {
		if (Raiz->UserCmp(User) && Raiz->PassCmp(Pass)) {
			return Raiz;
		}
		else {
			Empleado* auxizq = LogIn(Raiz->izq, User, Pass);
			Empleado* auxder = LogIn(Raiz->der, User, Pass);
			if (auxizq != 0) {
				return auxizq;
			}
			else if (auxder != 0) {
				return auxder;
			}
		}
	}
	
	return 0;
}

BOOL ArchivosSelectorUni(HWND Parent, char BUFF[], int SizeOfBuff)
{
	OPENFILENAME ofn;       // common dialog box structure
	LPWSTR aux = 0;
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Parent;
	ofn.lpstrFile = BUFF;
	ofn.nMaxFile = SizeOfBuff;
	ofn.lpstrFilter = "Bitmaps\0*.BMP\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE)
	{

		for (int I = 0; I < strlen(ofn.lpstrFile); I++) {
			BUFF[I] = ofn.lpstrFile[I];
		}

		return TRUE;
	}
	return FALSE;
}

//Escritura y lectura del arbol en archivos Binarios
void EscribirEnArchivoBinEmpleados(Empleado* Raiz) {
	static ofstream eout("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Employee.bin", ios::binary | ios::out | ios::trunc);
	if (Raiz != 0) {
		char Aux[5] = { NULL };

		_itoa_s(strlen(Raiz->Nombre) + 1 , Aux, 10);
		eout.write((char*)Aux, sizeof(Aux));
		eout.write((char*)Raiz->Nombre, strlen(Raiz->Nombre) + 1);
		memset(Aux, NULL, 5);

		_itoa_s(strlen(Raiz->Correo) + 1, Aux, 10);
		eout.write((char*)Aux, sizeof(Aux));
		eout.write((char*)Raiz->Correo, strlen(Raiz->Correo) + 1);
		memset(Aux, NULL, 5);

		//_itoa_s(strlen(this->Telefono) + 1, Aux, 10);
		//out.write((char*)Aux, sizeof(Aux));
		eout.write((char*)Raiz->Telefono, sizeof(Raiz->Telefono));
		//memset(Aux, NULL, strlen(this->Telefono));

		_itoa_s(strlen(Raiz->Usuario) + 1, Aux, 10);
		eout.write((char*)Aux, sizeof(Aux));
		eout.write((char*)Raiz->Usuario, strlen(Raiz->Usuario) + 1);
		memset(Aux, NULL, 5);

		_itoa_s(strlen(Raiz->Contraseña) + 1, Aux, 10);
		eout.write((char*)Aux, sizeof(Aux));
		eout.write((char*)Raiz->Contraseña, strlen(Raiz->Contraseña) + 1);
		memset(Aux, NULL, 5);

		_itoa_s(strlen(Raiz->buffer) + 1, Aux, 10);
		eout.write((char*)Aux, sizeof(Aux));
		eout.write((char*)Raiz->buffer, strlen(Raiz->buffer) + 1);
		memset(Aux, NULL, 5);

		EscribirEnArchivoBinEmpleados(Raiz->izq);
		EscribirEnArchivoBinEmpleados(Raiz->der);
	}
	if (Raiz == Empleados) {
		eout.close();
	}
}
void LeerArchivoBinEmpleados(Empleado* Raiz) {
	ifstream in("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Employee.bin", ios::binary | ios::in);
	if (in.is_open()) {
		in.seekg(0, in.end);
		std::streamoff endd = in.tellg();
		in.seekg(0, in.beg);
		while (in.tellg() < endd) {
			char IndAux[5] = { NULL };
			char* BUFF;
			Empleado* Nuevo = new Empleado;

			in.read((char*)IndAux, sizeof(IndAux));
			BUFF = new char[atoi(IndAux)]();
			in.read((char*)BUFF, atoi(IndAux));
			Nuevo->SetName(BUFF);
			memset(IndAux, NULL, 5);
			delete BUFF;

			in.read((char*)IndAux, sizeof(IndAux));
			BUFF = new char[atoi(IndAux)]();
			in.read((char*)BUFF, atoi(IndAux));
			Nuevo->SetMail(BUFF);
			memset(IndAux, NULL, 5);
			delete BUFF;

			//in.read((char*)IndAux, sizeof(IndAux));
			BUFF = new char[12]();
			in.read((char*)BUFF, 12);
			Nuevo->SetPhon(BUFF);
			//memset(IndAux, NULL, 5);
			delete BUFF;

			in.read((char*)IndAux, sizeof(IndAux));
			BUFF = new char[atoi(IndAux)]();
			in.read((char*)BUFF, atoi(IndAux));
			Nuevo->SetUser(BUFF);
			memset(IndAux, NULL, 5);
			delete BUFF;

			in.read((char*)IndAux, sizeof(IndAux));
			BUFF = new char[atoi(IndAux)]();
			in.read((char*)BUFF, atoi(IndAux));
			Nuevo->SetPass(BUFF);
			memset(IndAux, NULL, 5);
			delete BUFF;

			in.read((char*)IndAux, sizeof(IndAux));
			BUFF = new char[atoi(IndAux)]();
			in.read((char*)BUFF, atoi(IndAux));
			Nuevo->SetBuff(BUFF);
			memset(IndAux, NULL, 5);
			delete BUFF;

			AddLast(&Empleados, Nuevo);
		}
	}
	in.close();
}

//Escribir y leer información sobre las mesas
void WriteTableInfo(Mesa* Mesas) {
	ofstream out("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Table.bin", ios::binary | ios::out | ios::trunc);
	for (int I = 0; I < 15; I++) {
		out.write((char*)&Mesas[I], sizeof(Mesa));
	}
	out.close();
}
void ReadTableInfo(Mesa Mesas[]) {
	ifstream in("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Table.bin", ios::binary | ios::in);
	int I = 0;
	if (in.is_open()) {
		in.seekg(0, in.end);
		std::streamoff endd = in.tellg();
		in.seekg(0, in.beg);
		while (in.tellg() < endd && I < 15) {
			in.read((char*)&Mesas[I], sizeof(Mesa));
			I++;
		}
	}
}

//Escribir y leer informacion sobre las ordenes activas
void SaveOrders(const char Dir[],ListaLigada<Comienda>* Orders, const char DirT[], ListaLigada<Stuff>* OrdThings) {
	Orders->WriteList(Dir);
	OrdThings->WriteList(DirT);
}
void LoadOrders(const char Dir[], ListaLigada<Comienda>* Orders, const char DirT[], ListaLigada<Stuff>* OrdThings) {
	Orders->ReadList(Dir);
	OrdThings->ReadList(DirT);
}

//Hinstancia 
HINSTANCE hIns;

//HWND
HWND LogInWindow;
HWND UserWindow;
HWND AdminWindow;
HWND AddUserWindow;
HWND AddFoodWindow;
HWND OrderWindow;
HWND ConfirmWindow;
HWND MenuWindow;
HWND SelectorWindow;
HWND ListWindow;
HWND PayWindow;
HWND HistorialWindow;
HWND ConsulWindow;


int TakingCare = 0;
Mesa *SelectedTable = 0;
Nodo<Comienda>* SelectedNote;
Nodo<Stuff>* SelectedNoteStuff;

Mesa Mesas[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

bool DelEmployee = false;
bool EditFood = false;
bool DelFood = false;
Nodo<Alimento>* SelectedFood;

ListaLigada<ButtonList<Nodo<Nodo<Alimento>*>*>> FoodButtons;
ListaLigada<Nodo<Alimento>*> FoodPointers;
HFONT hFont = CreateFontA(10, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

BOOL CALLBACK MenuProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
	{
		char BUFF[300] = { NULL };
		EnableWindow(GetParent(hWnd), false);
		//Inicializamos el menú
		                  //POSTRE, BEBIDA, DESAYUNO, COMIDA, CENA
		int ButtonSize = 100;
		POINT Filas[5] = { {10,10},{10 + (ButtonSize + 20),10},{10 + (ButtonSize + 20)*2,10},{10 + (ButtonSize + 20)*3,10},{10 + (ButtonSize + 20)*4,10} };
		int LastId = 42069;
		int I = Alimentos.Count();
		Nodo<Nodo<Alimento>*>* FoodPointerNode = 0;
		for (int J = 0; J < I; J++) {
			FoodPointerNode = new Nodo<Nodo<Alimento>*>;
			FoodPointerNode->Datos = Alimentos[J];
			FoodPointers.AddLast(FoodPointerNode);
		}
		RECT rect;
		GetWindowRect(hWnd, &rect);
		FoodPointerNode = FoodPointers.head;
		DWORD ButtStyles =  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_BITMAP | BS_LEFT | BS_VCENTER;
		DWORD StaticStyles =  SS_LEFT  | WS_VISIBLE | WS_CHILD;
		//Escaneamos y creamos todos los botones para POSTRE
		while (FoodPointerNode != 0) {
			if (FoodPointerNode->Datos->Datos.GetCategory() == POSTRE) {
				Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>* NuevoBoton = new Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>(LastId);
				NuevoBoton->Datos.SetButtInfo(FoodPointerNode);
				LastId++;
				NuevoBoton->Datos.CrearBoton(Filas[0].x, Filas[0].y, ButtonSize, ButtonSize, ButtStyles, StaticStyles,hFont,hWnd,hIns);
				if (rect.bottom > Filas[0].y + 55) {
					Filas[0].y += ButtonSize +5;
				}
				else {
					Filas[0].x += ButtonSize + 5;
					Filas[0].y = 10;
					Filas[1].x += ButtonSize + 5;
					Filas[2].x += ButtonSize + 5;
					Filas[3].x += ButtonSize + 5;
					Filas[4].x += ButtonSize + 5;
				}
				FoodPointerNode->Datos->Datos.GetBuff(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetBitmap(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodPointerNode->Datos->Datos.GetName(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetStaticText(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodButtons.AddLast(NuevoBoton);
			}
			FoodPointerNode = FoodPointerNode->nxt;
		}
		FoodPointerNode = FoodPointers.head;
		//Ahora escaneamos y creamos todos los botones para BEBIDA

		while (FoodPointerNode != 0) {
			if (FoodPointerNode->Datos->Datos.GetCategory() == BEBIDA) {
				Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>* NuevoBoton = new Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>(LastId);
				NuevoBoton->Datos.SetButtInfo(FoodPointerNode);
				LastId++;
				NuevoBoton->Datos.CrearBoton(Filas[1].x, Filas[1].y, ButtonSize, ButtonSize, ButtStyles, StaticStyles, hFont, hWnd, hIns);
				if (rect.bottom > Filas[1].y + 55) {
					Filas[1].y += ButtonSize + 5;
				}
				else {
					Filas[1].x += ButtonSize +5;
					Filas[1].y = 10;
					Filas[2].x += ButtonSize + 5;
					Filas[3].x += ButtonSize + 5;
					Filas[4].x += ButtonSize + 5;
				}
				FoodPointerNode->Datos->Datos.GetBuff(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetBitmap(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodPointerNode->Datos->Datos.GetName(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetStaticText(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodButtons.AddLast(NuevoBoton);
			}
			FoodPointerNode = FoodPointerNode->nxt;
		}
		FoodPointerNode = FoodPointers.head;
		//Ahora escaneamos y creamos todos los botones para DESAYUNO
		while (FoodPointerNode != 0) {
			if (FoodPointerNode->Datos->Datos.GetCategory() == DESAYUNO) {
				Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>* NuevoBoton = new Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>(LastId);
				NuevoBoton->Datos.SetButtInfo(FoodPointerNode);
				LastId++;
				NuevoBoton->Datos.CrearBoton(Filas[2].x, Filas[2].y, ButtonSize , ButtonSize , ButtStyles, StaticStyles, hFont, hWnd, hIns);
				if (rect.bottom > Filas[2].y + 55) {
					Filas[2].y += ButtonSize + 5;
				}
				else {
					Filas[2].x += ButtonSize + 5;
					Filas[2].y = 10;
					Filas[3].x += ButtonSize + 5;
					Filas[4].x += ButtonSize + 5;
				}
				FoodPointerNode->Datos->Datos.GetBuff(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetBitmap(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodPointerNode->Datos->Datos.GetName(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetStaticText(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodButtons.AddLast(NuevoBoton);
			}
			FoodPointerNode = FoodPointerNode->nxt;
		}
		FoodPointerNode = FoodPointers.head;
		//Ahora escaneamos y creamos todos los botones para COMIDA
		while (FoodPointerNode != 0) {
			if (FoodPointerNode->Datos->Datos.GetCategory() == COMIDA) {
				Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>* NuevoBoton = new Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>(LastId);
				NuevoBoton->Datos.SetButtInfo(FoodPointerNode);
				LastId++;
				NuevoBoton->Datos.CrearBoton(Filas[3].x, Filas[3].y, ButtonSize, ButtonSize, ButtStyles, StaticStyles, hFont, hWnd, hIns);
				if (rect.bottom > Filas[3].y + 55) {
					Filas[3].y += ButtonSize + 5;
				}
				else {
					Filas[3].x += ButtonSize + 5;
					Filas[3].y = 10;
					Filas[4].x += ButtonSize + 5;
				}
				FoodPointerNode->Datos->Datos.GetBuff(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetBitmap(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodPointerNode->Datos->Datos.GetName(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetStaticText(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodButtons.AddLast(NuevoBoton);
			}
			FoodPointerNode = FoodPointerNode->nxt;
		}
		FoodPointerNode = FoodPointers.head;
		//Ahora escaneamos y creamos todos los botones para CENA
		while (FoodPointerNode != 0) {
			if (FoodPointerNode->Datos->Datos.GetCategory() == CENA) {
				Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>* NuevoBoton = new Nodo<ButtonList<Nodo<Nodo<Alimento>*>*>>(LastId);
				NuevoBoton->Datos.SetButtInfo(FoodPointerNode);
				LastId++;
				NuevoBoton->Datos.CrearBoton(Filas[4].x, Filas[4].y, ButtonSize, ButtonSize, ButtStyles, StaticStyles, hFont, hWnd, hIns);
				if (rect.bottom > Filas[4].y + 55) {
					Filas[4].y += ButtonSize + 5;
				}
				else {
					Filas[4].x += ButtonSize + 5;
					Filas[4].y = 10;
				}
				FoodPointerNode->Datos->Datos.GetBuff(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetBitmap(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodPointerNode->Datos->Datos.GetName(BUFF, sizeof(BUFF));
				NuevoBoton->Datos.SetStaticText(BUFF);
				memset(BUFF, NULL, strlen(BUFF));
				FoodButtons.AddLast(NuevoBoton);
			}
			FoodPointerNode = FoodPointerNode->nxt;
		}
	}
	break;
	case WM_COMMAND:
	{
		//Usar truco para botones dinamicos
		if (wParam >= 42069) {
			char BUFF[200] = { NULL };
			int I = SendMessage(GetDlgItem(OrderWindow, IDC_LISTCLIENT), LB_GETCURSEL, NULL, NULL);
			//Agregamos el Alimento al consumo
			Nodo<Stuff>* NewNodePointer = new Nodo<Stuff>;
			NewNodePointer->Datos.ClientNum = I;
			NewNodePointer->Datos.Folio = SelectedNote->Datos.GetFolio();
			NewNodePointer->Datos.FoodID = FoodButtons[(int)wParam - 42069]->Datos.GetButtInfo()->Datos->Datos.GetID();
			NewNodePointer->Datos.FoodPrice = FoodButtons[(int)wParam - 42069]->Datos.GetButtInfo()->Datos->Datos.GetPrice();
			if (SelectedNoteStuff != 0) {
				OrdStuff.InsertBehindOf(SelectedNoteStuff, NewNodePointer);
			}
			else {
				OrdStuff.AddFirst(NewNodePointer);
				SelectedNoteStuff = NewNodePointer;
			}
			//Agregamos el nombre del Alimento a la ListBox en la ventana
			FoodButtons[(int)wParam - 42069]->Datos.GetButtInfo()->Datos->Datos.GetName(BUFF, sizeof(BUFF));
			SendMessage(GetDlgItem(OrderWindow, IDC_LISTCONSUME), LB_ADDSTRING, NULL, (LPARAM)BUFF);
		}
	}
	break;
	case WM_CLOSE:
	{
		FoodButtons.DeleteList();
		FoodPointers.DeleteList();
		EnableWindow(GetParent(hWnd), true);
		DestroyWindow(hWnd);
	}
	break;
	default:
		break;
	}
	return 0;
}

bool DelClient = false;

BOOL CALLBACK ConfirmProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static char BUFF[100] = { NULL };
	switch (msg) {
	case WM_INITDIALOG:
	{
		EnableWindow(GetParent(hWnd), false);
	}
	break;
	case WM_COMMAND:
	{
		switch (wParam) {
		case IDOK:
		{
			GetWindowText(GetDlgItem(hWnd, IDC_CONTRASENA), BUFF, sizeof(BUFF));
			if (strcmp(BUFF, AdminPass) == 0) {
				if (DelClient) {
					int I = SendMessage(GetDlgItem(OrderWindow, IDC_LISTCLIENT), LB_GETCURSEL, NULL, NULL);
					SendMessage(GetDlgItem(OrderWindow, IDC_LISTCLIENT), LB_DELETESTRING, I, NULL);
					while (SelectedNoteStuff != 0) {
						if (SelectedNoteStuff->Datos.Folio != SelectedNote->Datos.GetFolio()) {
							break;
						}
						if (SelectedNoteStuff->Datos.ClientNum == I) {
							Nodo<Stuff>*Aux = SelectedNoteStuff;
							SelectedNoteStuff = SelectedNoteStuff->nxt;
							OrdStuff.Remove(Aux);
						}
						else {
							if (SelectedNoteStuff->Datos.ClientNum > I) {
								SelectedNoteStuff->Datos.ClientNum--;
							}
							SelectedNoteStuff = SelectedNoteStuff->nxt;
						}
					}
					SelectedNoteStuff = SearchStuffByFolio(&OrdStuff, SelectedNote->Datos.GetFolio());
					//SelectedNote->Datos.Clientes.Remove(SelectedNote->Datos.Clientes[I]);
					memset(BUFF, NULL, strlen(BUFF));
					I = SelectedNote->Datos.GetClientNum() - 1;
					SelectedNote->Datos.SetClientNum(I);
					_itoa_s(I, BUFF, 10);
					SetWindowText(GetDlgItem(OrderWindow, IDC_EDITCLIENTNUM), BUFF);

					int P = SendMessage(GetDlgItem(OrderWindow, IDC_LISTCONSUME), LB_GETCOUNT, NULL, NULL);
					for (int Q = 0; Q < P; Q++) {
						SendMessage(GetDlgItem(OrderWindow, IDC_LISTCONSUME), LB_DELETESTRING, 0, NULL);
					}
				}
				else {
					//Conseguimos los 2 indices a partir de la seleccion de las listas y eliminamos
					int I = SendMessage(GetDlgItem(OrderWindow, IDC_LISTCLIENT), LB_GETCURSEL, NULL, NULL);
					int J = SendMessage(GetDlgItem(OrderWindow, IDC_LISTCONSUME), LB_GETCURSEL, NULL, NULL);
					if (I != LB_ERR) {
						if (J != LB_ERR) {
							while (SelectedNoteStuff != 0) {
								if (SelectedNoteStuff->Datos.Folio != SelectedNote->Datos.GetFolio()) {
									break;
								}
								if (SelectedNoteStuff->Datos.ClientNum == I) {
									char BUFF[100] = { NULL };
									SendMessage(GetDlgItem(OrderWindow, IDC_LISTCONSUME), LB_GETTEXT, J, (LPARAM)BUFF);
									if (SelectedNoteStuff->Datos.FoodID == Search(&Alimentos, BUFF)->Datos.GetID()) {
										Nodo<Stuff>*Aux = SelectedNoteStuff;
										SelectedNoteStuff = SelectedNoteStuff->nxt;
										OrdStuff.Remove(Aux);
									}
								}
								SelectedNoteStuff = SelectedNoteStuff->nxt;
							}
							SelectedNoteStuff = SearchStuffByFolio(&OrdStuff, SelectedNote->Datos.GetFolio());
							//SelectedNote->Datos.Clientes[I]->Datos.Consumo.Remove(SelectedNote->Datos.Clientes[I]->Datos.Consumo[J]);
							SendMessage(GetDlgItem(OrderWindow, IDC_LISTCONSUME), LB_DELETESTRING, J, NULL);
						}
						else {
							MessageBoxA(hWnd, "Primero seleccione un consumo para llevar a cabo esta acción", "Notificacion", MB_OK | MB_ICONHAND);
						}
					}
					else {
						MessageBoxA(hWnd, "Primero seleccione un cliente para llevar a cabo esta acción", "Notificacion", MB_OK | MB_ICONHAND);
					}
				}
				memset(BUFF, NULL, strlen(BUFF));
				EnableWindow(GetParent(hWnd), true);
				DestroyWindow(hWnd);
				return 1;
			}
			else {
				MessageBoxA(hWnd, "La contraseña no concuerda con la que se encuentra en los registros", "Acceso Denegado", MB_OK | MB_ICONHAND);
				break;
			}
		}
		break;
		default:
			break;
		}
	}
	break;
	case WM_CLOSE: 
	{
		memset(BUFF, NULL, strlen(BUFF));
		EnableWindow(GetParent(hWnd), true);
		DestroyWindow(hWnd);
	}	
	break;
	default:
		break;
	}
	return 0;
}

BOOL CALLBACK OrderProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	char BUFF[4] = { NULL };
	char Aux[11] = { "Cliente" };
	switch (msg) {
	case WM_INITDIALOG:
	{
		EnableWindow(GetParent(hWnd), false);
		SetWindowText(GetDlgItem(hWnd, IDC_EDITIP), "0");
		SetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), "0");
		_itoa_s(SelectedTable->GetTableNum(),BUFF,10);
		SetWindowText(GetDlgItem(hWnd, IDC_STATICTABLE), BUFF);
		memset(BUFF, NULL, strlen(BUFF));
		if (SelectedNote == 0) {
			//Crear nueva nota y agregarla a la lista
			Nodo<Comienda>* Nuevo = new Nodo<Comienda>;
			SelectedNote = Nuevo;
			SelectedNote->Datos.SetTable(SelectedTable);
			Ordenes.AddLast(SelectedNote);
			SelectedNoteStuff = 0;
		}
		else {
			//Cargamos la nota ya existente
			SelectedNoteStuff = SearchStuffByFolio(&OrdStuff, SelectedNote->Datos.GetFolio());
			int I = SelectedNote->Datos.GetClientNum();
			_itoa_s(I, BUFF, 10);
			SetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), BUFF);
			for (int J = 0; J < I; J++) {
				char aux[11] = { "Cliente" };
				_itoa_s(J + 1 , BUFF, 10);
				strcat_s(aux, BUFF);
				SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_ADDSTRING, NULL, (LPARAM)aux);
			}
			//Cargamos la propina
			_itoa_s(SelectedNote->Datos.GetTip()*100, BUFF, 10);
			SetWindowText(GetDlgItem(hWnd, IDC_EDITIP), BUFF);
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (wParam) {
		case IDC_BUTTIZQ:
		{
			// --
			GetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), BUFF, sizeof(BUFF));
			int I = atoi(BUFF) - 1;
			//Validacion para asegurar que desea eliminar un cliente con consumo y pedir contraseña del administrador para hacerlo
			if (I >= 0) {
				bool Consume = true;
				while (SelectedNoteStuff != 0) {
					if (SelectedNoteStuff->Datos.Folio != SelectedNote->Datos.GetFolio()) {
						break;
					}
					if (SelectedNoteStuff->Datos.ClientNum == I) {
						Consume = false;
						break;
					}
					else {
						SelectedNoteStuff = SelectedNoteStuff->nxt;
					}
				}
				if (Consume) {
					//I--;
					SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_DELETESTRING, I, NULL);
					SelectedNote->Datos.SetClientNum(SelectedNote->Datos.GetClientNum() - 1);
					memset(BUFF, NULL, strlen(BUFF));
					_itoa_s(I, BUFF, 10);
					SetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), BUFF);
				}
				else {
					//Avisarle que el cliente que está a punto de eliminar tiene consumo
					int R = MessageBoxA(hWnd, "El cliente que está a punto de eliminar tiene consumo en su lista, si desea continuar va a requerir confirmaccion de un Administrador", "Notificacion", MB_YESNO | MB_ICONEXCLAMATION);
					if (R == IDYES) {
						//Pedir permiso para eliminar
						ConfirmWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_CONFIRM), hWnd, (DLGPROC)ConfirmProc, 0);
						ShowWindow(ConfirmWindow, SW_SHOW);
						if (DelClient) {
							//I--;
							SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_DELETESTRING, I, NULL);
							while (SelectedNoteStuff != 0) {
								if (SelectedNoteStuff->Datos.Folio != SelectedNote->Datos.GetFolio()) {
									break;
								}
								if (SelectedNoteStuff->Datos.ClientNum == I) {
									Nodo<Stuff>*Aux = SelectedNoteStuff;
									SelectedNoteStuff = SelectedNoteStuff->nxt;
									OrdStuff.Remove(Aux);
								}
								else {
									SelectedNoteStuff = SelectedNoteStuff->nxt;
								}
							}
							SelectedNoteStuff = SearchStuffByFolio(&OrdStuff, SelectedNote->Datos.GetFolio());
							SelectedNote->Datos.SetClientNum(SelectedNote->Datos.GetClientNum() - 1);
							memset(BUFF, NULL, strlen(BUFF));
							_itoa_s(I, BUFF, 10);
							SetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), BUFF);
						}
					}
				}
			}
		}
		break;
		case IDC_BUTTDER:
		{
			// ++
			GetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), BUFF, sizeof(BUFF));
			int I = atoi(BUFF);
			I++;
			memset(BUFF, NULL, strlen(BUFF));
			_itoa_s(I, BUFF, 10);
			SetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), BUFF);
			//Agregamos un nuevo Nodo al arreglo
			SelectedNote->Datos.SetClientNum(SelectedNote->Datos.GetClientNum() + 1);
			strcat_s(Aux, BUFF);
			SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_ADDSTRING, NULL, (LPARAM)Aux);
		}
		break;
		case IDC_DELCLIENT:
		{
			int I = SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_GETCURSEL, NULL, NULL);
			if (I != LB_ERR && I >= 0) {
				bool Consume = true;
				while (SelectedNoteStuff != 0) {
					if (SelectedNoteStuff->Datos.Folio != SelectedNote->Datos.GetFolio()) {
						break;
					}
					if (SelectedNoteStuff->Datos.ClientNum == I) {
						Consume = false;
						break;
					}
					else {
						SelectedNoteStuff = SelectedNoteStuff->nxt;
					}
				}
				SelectedNoteStuff = SearchStuffByFolio(&OrdStuff, SelectedNote->Datos.GetFolio());
				if (Consume) {
						//I--;
						SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_DELETESTRING, I, NULL);
						SelectedNote->Datos.SetClientNum(SelectedNote->Datos.GetClientNum() - 1);
						memset(BUFF, NULL, strlen(BUFF));
						I = SelectedNote->Datos.GetClientNum();
						_itoa_s(I, BUFF, 10);
						SetWindowText(GetDlgItem(hWnd, IDC_EDITCLIENTNUM), BUFF);
					
				}
				else {
					//Avisarle que el cliente que está a punto de eliminar tiene consumo
					int R = MessageBoxA(hWnd, "El cliente que está a punto de eliminar tiene consumo en su lista, si desea continuar va a requerir confirmaccion de un Administrador", "Notificacion", MB_YESNO | MB_ICONEXCLAMATION);
					if (R == IDYES) {
						//Pedir permiso para eliminar
						DelClient = true;
						ConfirmWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_CONFIRM), hWnd, (DLGPROC)ConfirmProc, 0);
						ShowWindow(ConfirmWindow, SW_SHOW);
					}
				}
			}
			else {
				MessageBoxA(hWnd, "Primero seleccione un cliente para llevar a cabo esta acción", "Notificacion", MB_OK | MB_ICONHAND);
			}
		}
		break;
		case IDC_ADDCONS:
		{
			int I = SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_GETCURSEL, NULL, NULL);
			if (I != LB_ERR) {
				MenuWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_SELCONSUME), hWnd, (DLGPROC)MenuProc, 0);
				ShowWindow(MenuWindow, SW_SHOW);
			}
			else {
				MessageBoxA(hWnd, "Primero seleccione un cliente para llevar a cabo esta acción", "Notificacion", MB_OK | MB_ICONHAND);
			}
		}
		break;
		case IDC_DELCONSUME:
		{
			int R = MessageBoxA(hWnd, "Está a punto de eliminar el consumo de un cliente, si desea continuar va a requerir confirmaccion de un Administrador", "Notificacion", MB_YESNO | MB_ICONEXCLAMATION);
			if (R == IDYES) {
				//Pedir permiso para eliminar
				ConfirmWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_CONFIRM), hWnd, (DLGPROC)ConfirmProc, 0);
				ShowWindow(ConfirmWindow, SW_SHOW);
			}

		}
		break;
		case IDOK:
		{
			int R = MessageBoxA(hWnd, "¿Está seguro que desea finalizar la cuenta?", "Confirmacion", MB_YESNO | MB_ICONEXCLAMATION);
			if (R == IDYES) {
				OrderXChange(SelectedNote->Datos.GetFolio(), &Ordenes, &OrdStuff, &Pendientes, &PendStuff);
				SelectedTable->SetState(OCUPADA);
				SelectedTable = 0;
				SelectedNote = 0;
				EnableWindow(GetParent(hWnd), true);
				DestroyWindow(hWnd);
			}
		}
		break;
		}
		switch (HIWORD(wParam)) {
		case LBN_SELCHANGE:
		{
			switch (LOWORD(wParam)) {
			case IDC_LISTCLIENT:
			{
				int P = SendMessage(GetDlgItem(hWnd, IDC_LISTCONSUME), LB_GETCOUNT, NULL, NULL);
				for (int Q = 0; Q < P; Q++) {
					SendMessage(GetDlgItem(hWnd, IDC_LISTCONSUME), LB_DELETESTRING, 0, NULL);
				}
				int J = SendMessage(GetDlgItem(hWnd, IDC_LISTCLIENT), LB_GETCURSEL, NULL, NULL);
				//int K = SelectedNote->Datos.Clientes[J]->Datos.Consumo.Count();
				
				char Food[200] = { NULL };
				while (SelectedNoteStuff != 0) {
					if (SelectedNoteStuff->Datos.Folio != SelectedNote->Datos.GetFolio()) {
						break;
					}
					if (SelectedNoteStuff->Datos.ClientNum == J) {
						SearchFoodByID(&Alimentos, SelectedNoteStuff->Datos.FoodID)->Datos.GetName(Food, sizeof(Food));
						SendMessage(GetDlgItem(hWnd, IDC_LISTCONSUME), LB_ADDSTRING, NULL, (LPARAM)Food);
						memset(Food, NULL, strlen(Food));
					}
						
					SelectedNoteStuff = SelectedNoteStuff->nxt;
						
				}
				SelectedNoteStuff = SearchStuffByFolio(&OrdStuff, SelectedNote->Datos.GetFolio());

					
				
			}
			break;
			}
		}
		break;
		}
	}
	break;
	case WM_CLOSE:
	{
		GetWindowText(GetDlgItem(hWnd, IDC_EDITIP), BUFF, sizeof(BUFF));
		SelectedNote->Datos.SetTip(atof(BUFF)/100);
		SelectedTable = 0;
		SelectedNote = 0;
		EnableWindow(GetParent(hWnd), true);
		DestroyWindow(hWnd);
	}
	break;
	}

	return 0;
}

BOOL CALLBACK AddFoodProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static char BUFF[300] = { NULL };
	if (EditFood) {
		//Si es la ventana de editar la comida
		switch (msg) {
		case WM_INITDIALOG:
		{

			SendMessage(GetDlgItem(hWnd, IDC_NOMBRE), EM_LIMITTEXT, 200, 0);
			SendMessage(GetDlgItem(hWnd, IDC_PRICE), EM_LIMITTEXT, 10, 0);
			//Cargamos el nombre del SelectedFood
			SelectedFood->Datos.GetName(BUFF, sizeof(BUFF));
			SetWindowText(GetDlgItem(hWnd, IDC_NOMBRE), BUFF);
			memset(BUFF, NULL, strlen(BUFF));
			//Cargamos el precio del SelectedFood
			sprintf_s(BUFF, "%.2f", SelectedFood->Datos.GetPrice());
			SetWindowText(GetDlgItem(hWnd, IDC_PRICE), BUFF);
			memset(BUFF, NULL, strlen(BUFF));

			//Cargamos el ComboBox
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Postre");
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Bebida");
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Desayuno");
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Comida");
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Cena");

			//Ahora le decimos la categoria del SelectedFood
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_SETCURSEL, SelectedFood->Datos.GetCategory(), NULL);

			//Cargamos la imagen ya cargada del SelectedFood
			RECT rect;
			GetWindowRect(GetDlgItem(hWnd, IDC_FOTO), &rect);
			SelectedFood->Datos.GetBuff(BUFF, sizeof(BUFF));
			HBITMAP Perfil = (HBITMAP)LoadImage(NULL, BUFF , IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			SendMessage(GetDlgItem(hWnd, IDC_FOTO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Perfil);
		}
		break;
		case WM_COMMAND:
		{
			switch (wParam) {
			case IDCANCEL:
			{
				memset(BUFF, NULL, strlen(BUFF));
				EditFood = false;
				DestroyWindow(hWnd);

			}
			break;
			case IDOK:
			{
				char aux[300] = { NULL };
				Nodo<Alimento>* Nuevo = new Nodo<Alimento>;
				char ConfimBuffer[50] = { NULL };
				char Errores[600] = { NULL };
				GetWindowTextA(GetDlgItem(hWnd, IDC_NOMBRE), aux, sizeof(aux));
				if (!ValName(aux, sizeof(aux))) {
					strcat_s(Errores, "-Nombre invalido \n");
				}
				Nuevo->Datos.SetName(aux);
				memset(aux, NULL, strlen(aux));

				GetWindowTextA(GetDlgItem(hWnd, IDC_PRICE), aux, sizeof(aux));
				if (!atof(aux)) {
					strcat_s(Errores, "-Precio invalido \n");
				}
				Nuevo->Datos.SetPrice(atof(aux));
				memset(aux, NULL, strlen(aux));

				GetWindowTextA(GetDlgItem(hWnd, IDC_COMBO1), aux, sizeof(aux));
				if (aux[0] == NULL) {
					strcat_s(Errores, "-Seleccione una categoria \n");
				}
				else if (strcmp(aux, "Postre") == 0) {
					Nuevo->Datos.SetCategory(POSTRE);
				}
				else if (strcmp(aux, "Bebida") == 0) {
					Nuevo->Datos.SetCategory(BEBIDA);
				}
				else if (strcmp(aux, "Desayuno") == 0) {
					Nuevo->Datos.SetCategory(DESAYUNO);
				}
				else if (strcmp(aux, "Comida") == 0) {
					Nuevo->Datos.SetCategory(COMIDA);
				}
				else if (strcmp(aux, "Cena") == 0) {
					Nuevo->Datos.SetCategory(CENA);
				}
				memset(aux, NULL, strlen(aux));

				if (BUFF[0] == NULL) {
					strcat_s(Errores, "-Agregue una foto \n");
				}
				else {
					Nuevo->Datos.SetBuff(BUFF);
				}

				if (Errores[0] != NULL) {
					delete Nuevo;
					MessageBox(hWnd, Errores, "Lista de Errores", MB_OK | MB_ICONHAND);
					memset(Errores, NULL, strlen(Errores));
					memset(ConfimBuffer, NULL, strlen(ConfimBuffer));
				}
				else {
					//AGREGAR
					Alimentos.Remove(SelectedFood);
					Alimentos.AddLast(Nuevo);
					EditFood = false;
					DestroyWindow(hWnd);
				}

			}
			break;
			case IDC_SELECT:
			{
				memset(BUFF, NULL, strlen(BUFF));

				if (ArchivosSelectorUni(hWnd, BUFF, sizeof(BUFF)) == TRUE) {
					RECT rect;
					HBITMAP LOAD;
					GetWindowRect(GetDlgItem(hWnd, IDC_FOTO), &rect);
					LOAD = (HBITMAP)LoadImage(NULL, BUFF, IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
					SendDlgItemMessage(hWnd, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LOAD);
				}
			}
			break;
			}

		}
		break;
		case WM_CLOSE:
		{
			memset(BUFF, NULL, strlen(BUFF));
			DestroyWindow(hWnd);
		}
		break;

		}
	}
	else {
	switch (msg) {
	case WM_INITDIALOG:
	{

		SendMessage(GetDlgItem(hWnd, IDC_NOMBRE), EM_LIMITTEXT, 200, 0);
		SendMessage(GetDlgItem(hWnd, IDC_PRICE), EM_LIMITTEXT, 10, 0);

		//Cargamos el ComboBox
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Postre");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Bebida");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Desayuno");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Comida");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Cena");

		RECT rect;
		GetWindowRect(GetDlgItem(hWnd, IDC_FOTO), &rect);
		HBITMAP Perfil = (HBITMAP)LoadImage(NULL, "Interr.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		SendMessage(GetDlgItem(hWnd, IDC_FOTO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Perfil);
	}
	break;
	case WM_COMMAND:
	{
		switch (wParam) {
		case IDCANCEL:
		{
			memset(BUFF, NULL, strlen(BUFF));
			DestroyWindow(hWnd);

		}
		break;
		case IDOK:
		{
			char aux[300] = { NULL };
			Nodo<Alimento>* Nuevo = new Nodo<Alimento>;
			char ConfimBuffer[50] = { NULL };
			char Errores[600] = { NULL };
			GetWindowTextA(GetDlgItem(hWnd, IDC_NOMBRE), aux, sizeof(aux));
			if (!ValName(aux, sizeof(aux))) {
				strcat_s(Errores, "-Nombre invalido \n");
			}
			Nuevo->Datos.SetName(aux);
			memset(aux, NULL, strlen(aux));

			GetWindowTextA(GetDlgItem(hWnd, IDC_PRICE), aux, sizeof(aux));
			if (!atof(aux)) {
				strcat_s(Errores, "-Precio invalido \n");
			}
			Nuevo->Datos.SetPrice(atof(aux));
			memset(aux, NULL, strlen(aux));

			GetWindowTextA(GetDlgItem(hWnd, IDC_COMBO1), aux, sizeof(aux));
			if (aux[0] == NULL) {
				strcat_s(Errores, "-Seleccione una categoria \n");
			}
			else if (strcmp(aux, "Postre") == 0) {
				Nuevo->Datos.SetCategory(POSTRE);
			}
			else if (strcmp(aux, "Bebida") == 0) {
				Nuevo->Datos.SetCategory(BEBIDA);
			}
			else if (strcmp(aux, "Desayuno") == 0) {
				Nuevo->Datos.SetCategory(DESAYUNO);
			}
			else if (strcmp(aux, "Comida") == 0) {
				Nuevo->Datos.SetCategory(COMIDA);
			}
			else if (strcmp(aux, "Cena") == 0) {
				Nuevo->Datos.SetCategory(CENA);
			}
			memset(aux, NULL, strlen(aux));

			if (BUFF[0] == NULL) {
				strcat_s(Errores, "-Agregue una foto \n");
			}
			else {
				Nuevo->Datos.SetBuff(BUFF);
			}

			if (Errores[0] != NULL) {
				delete Nuevo;
				MessageBox(hWnd, Errores, "Lista de Errores", MB_OK | MB_ICONHAND);
				memset(Errores, NULL, strlen(Errores));
				memset(ConfimBuffer, NULL, strlen(ConfimBuffer));
			}
			else {
				//AGREGAR
				Alimentos.AddLast(Nuevo);
				DestroyWindow(hWnd);
			}

		}
		break;
		case IDC_SELECT:
		{
			if (ArchivosSelectorUni(hWnd, BUFF, sizeof(BUFF)) == TRUE) {
				RECT rect;
				HBITMAP LOAD;
				GetWindowRect(GetDlgItem(hWnd, IDC_FOTO), &rect);
				LOAD = (HBITMAP)LoadImage(NULL, BUFF, IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LOAD);
			}
		}
		break;
		}

	}
	break;
	case WM_CLOSE:
	{
		memset(BUFF, NULL, strlen(BUFF));
		DestroyWindow(hWnd);
	}
	break;

	}
}
	return 0;
}

BOOL CALLBACK AddUserProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static char BUFF[260] = { NULL };
	switch (msg) {
	case WM_INITDIALOG:
	{

		SendMessage(GetDlgItem(hWnd, IDC_NOMBRE), EM_LIMITTEXT, 100, 0);
		SendMessage(GetDlgItem(hWnd, IDC_PHONE), EM_LIMITTEXT, 11, 0);
		SendMessage(GetDlgItem(hWnd, IDC_MAIL), EM_LIMITTEXT, 100, 0);
		SendMessage(GetDlgItem(hWnd, IDC_USUARIO), EM_LIMITTEXT, 50, 0);
		SendMessage(GetDlgItem(hWnd, IDC_CONTRASENA1), EM_LIMITTEXT, 50, 0);
		SendMessage(GetDlgItem(hWnd, IDC_CONTRASENA2), EM_LIMITTEXT, 50, 0);

		RECT rect;
		GetWindowRect(GetDlgItem(hWnd, IDC_FOTO), &rect);
		HBITMAP Perfil = (HBITMAP)LoadImage(NULL, "Perfil.bmp", IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		SendMessage(GetDlgItem(hWnd, IDC_FOTO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Perfil);
	}
	break;
	case WM_COMMAND:
	{
		switch (wParam) {
		case IDCANCEL:
		{
			memset(BUFF, NULL, strlen(BUFF));
			DestroyWindow(hWnd);

		}
		break;
		case IDOK:
		{
			char aux[300] = { NULL };
			Empleado *Nuevo = new Empleado;
			char ConfimBuffer[50] = { NULL };
			char Errores[600] = { NULL };
			GetWindowTextA(GetDlgItem(hWnd, IDC_NOMBRE), aux, sizeof(aux));
			if (!ValName(aux, sizeof(aux))) {
				strcat_s(Errores, "-Nombre y Apellido invalido \n");
			}
			Nuevo->SetName(aux);
			memset(aux, NULL, strlen(aux));
			

			GetWindowTextA(GetDlgItem(hWnd, IDC_PHONE), aux, sizeof(aux));
			if (!ValPhon(aux)) {
				strcat_s(Errores, "-Numero telefonico invalido \n");
			}
			Nuevo->SetPhon(aux);
			memset(aux, NULL, strlen(aux));

			GetWindowTextA(GetDlgItem(hWnd, IDC_MAIL), aux, sizeof(aux));
			if (!ValMail(aux)) {
				strcat_s(Errores, "-Direccion de Correo invalida \n");
			}
			Nuevo->SetMail(aux);
			memset(aux, NULL, strlen(aux));

			GetWindowTextA(GetDlgItem(hWnd, IDC_USUARIO), aux, sizeof(aux));
			if (ValUser(Empleados,aux)) {
				strcat_s(Errores, "-Nombre de Usuario ya está en uso \n");
			}
			Nuevo->SetUser(aux);
			memset(aux, NULL, strlen(aux));

			GetWindowTextA(GetDlgItem(hWnd, IDC_CONTRASENA1), aux, sizeof(aux));
			GetWindowTextA(GetDlgItem(hWnd, IDC_CONTRASENA2), ConfimBuffer, sizeof(ConfimBuffer));
			if (!ValPass(aux, ConfimBuffer)) {
				strcat_s(Errores, "-La contraseña no coincide con la confirmacion \n");

			}
			Nuevo->SetPass(aux);
			memset(aux, NULL, strlen(aux));

			Nuevo->SetBuff(BUFF);
			//strcpy_s(Nuevo->buffer, BUFF);
			
			if(Errores[0] != NULL) {
				delete Nuevo;
				MessageBox(hWnd, Errores, "Lista de Errores", MB_OK | MB_ICONHAND);
				memset(Errores, NULL, strlen(Errores));
				memset(ConfimBuffer, NULL, strlen(ConfimBuffer));
			}
			else {
				//AGREGAR
				AddLast(&Empleados, Nuevo);
				DestroyWindow(hWnd);
			}

		}
		break;
		case IDC_SELECT:
		{
			if (ArchivosSelectorUni(hWnd, BUFF,sizeof(BUFF)) == TRUE) {
				RECT rect;
				HBITMAP LOAD;
				GetWindowRect(GetDlgItem(hWnd, IDC_FOTO), &rect);
				LOAD = (HBITMAP)LoadImage(NULL, BUFF, IMAGE_BITMAP, rect.right - rect.left, rect.bottom - rect.top, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LOAD);
			}
		}
		break;
		}

	}
	break;
	case WM_CLOSE:
	{
		memset(BUFF, NULL, strlen(BUFF));
		DestroyWindow(hWnd);
	}
	break;

	}
	return 0;
}

BOOL CALLBACK SelectorProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (EditFood) {
		switch (msg) {
		case WM_INITDIALOG:
		{
			//Cargamos con la lista completa de alimentos
			Nodo<Alimento>* aux = Alimentos.head;
			while (aux != 0) {
				char BUFF[200] = { NULL };
				aux->Datos.GetName(BUFF, sizeof(BUFF));
				SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_ADDSTRING, NULL, (LPARAM)BUFF);
				aux = aux->nxt;
			}
		}
		break;
		case WM_COMMAND:
		{
			switch (wParam) {
			case IDOK:
			{
				int I = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, NULL, NULL);
				if (I != LB_ERR) {
					SelectedFood = Alimentos[I];
					AddFoodWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_AGREALIM), hWnd, (DLGPROC)AddFoodProc, 0);
					ShowWindow(AddFoodWindow, SW_SHOW);
					//DestroyWindow(hWnd);
				}
				else {
					MessageBoxA(hWnd, "Primero seleccione un elemento de la lista.", "Notificacion", MB_OK | MB_ICONHAND);
				}
			}
			break;
			case IDCANCEL:
			{
				EditFood = false;
				DestroyWindow(hWnd);
			}
			break;
			default:
				break;
			}
		}
		break;
		case WM_CLOSE:
		{
			EditFood = false;
			DestroyWindow(hWnd);
		}
		break;
		default:
			break;
		}
	}
	else if (DelFood) {
		switch (msg) {
		case WM_INITDIALOG:
		{
			//Cargamos con la lista completa de alimentos
			Nodo<Alimento>* aux = Alimentos.head;
			while (aux != 0) {
				char BUFF[200] = { NULL };
				aux->Datos.GetName(BUFF, sizeof(BUFF));
				SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_ADDSTRING, NULL, (LPARAM)BUFF);
				aux = aux->nxt;
			}
		}
		break;
		case WM_COMMAND:
		{
			switch (wParam) {
			case IDOK:
			{
				int I = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, NULL, NULL);
				if (I != LB_ERR) {
					int R = MessageBoxA(hWnd, "¿Está seguro que desea eliminar este elemento? Esto es permanente", "Confirmacion", MB_YESNO | MB_ICONQUESTION);
					if (R == IDYES) {
						Alimentos.Remove(Alimentos[I]);
						DelFood = false;
						DestroyWindow(hWnd);
					}
				}
				else {
					MessageBoxA(hWnd, "Primero seleccione un elemento de la lista.", "Notificacion", MB_OK | MB_ICONHAND);
				}
			}
			break;
			case IDCANCEL:
			{
				DelFood = false;
				DestroyWindow(hWnd);
			}
			break;
			default:
				break;
			}
		}
		break;
		case WM_CLOSE:
		{
			DelFood = false;
			DestroyWindow(hWnd);;
		}
		break;
		default:
			break;
		}
	}
	
	return 0;
}

//Se usa para compactar el swith de WM_COMMAND en UserProc
void TableSwitch(HWND hWnd, Mesa *Table, int *TakingCareOf) {
	switch (Table->GetState()) {
	case LIBRE:
	{
		if (*TakingCareOf < 5) {
			Table->SetWorker(LoggedInUser);
			*TakingCareOf= *TakingCareOf + 1;
			MessageBoxA(hWnd, "Has tomado control sobre esta mesa", "Notificacion", MB_OK | MB_ICONINFORMATION);
		}
		else {
			MessageBoxA(hWnd, "Ya estás a cargo de suficientes mesas", "Notificacion", MB_OK | MB_ICONSTOP);
		}
	}
	break;
	case OCUPADA:
	{
		int R = MessageBoxA(hWnd, "¿Desea iniciar una cuenta en esta mesa?", "Confirmacion", MB_YESNO | MB_ICONQUESTION);
		switch (R) {
		case IDYES:
		{
			Table->SetState(EN_USO);
			SelectedTable = Table;
			OrderWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_ORDERING), hWnd, (DLGPROC)OrderProc, 0);
			ShowWindow(OrderWindow, SW_SHOW);
		}
		break;
		default:
			break;
		}
		
	}
	break;
	case EN_USO:
	{
		SelectedTable = Table;
		SelectedNote = SearchOrderByTable(&Ordenes, Table);
		OrderWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_ORDERING), hWnd, (DLGPROC)OrderProc, 0);
		ShowWindow(OrderWindow, SW_SHOW);
	}
	break;
	}
}

bool Extern = false;

BOOL CALLBACK UserProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	switch (msg) {
	case WM_INITDIALOG:
	{
		EnableWindow(GetParent(hWnd), FALSE);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		HBITMAP LayOut = (HBITMAP)LoadImage(NULL, "restaurant-layout.bmp", IMAGE_BITMAP, rect.right - rect.left -16, rect.bottom - rect.top -38, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		HWND hImageView = CreateWindow("STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd,NULL,hIns,NULL);
		SendMessage(hImageView, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LayOut);
		ShowWindow(hImageView, SW_SHOW);

		if (!Extern) {
			ReadTableInfo(Mesas);
			LoadOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Ordenes.bin", &Ordenes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\OrdStuff.bin", &OrdStuff);
			LoadOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Pendientes.bin", &Pendientes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\PendStuff.bin", &PendStuff);
			LoadOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Historial.bin", &Historial, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\HistStuff.bin", &HistStuff);
		}

		Mesas[0].CreateButton(hWnd, hIns, Mesas[0].GetState());
		Mesas[1].CreateButton(hWnd, hIns, Mesas[1].GetState());
		Mesas[2].CreateButton(hWnd, hIns, Mesas[2].GetState());
		Mesas[3].CreateButton(hWnd, hIns, Mesas[3].GetState());
		Mesas[4].CreateButton(hWnd, hIns, Mesas[4].GetState());
		Mesas[5].CreateButton(hWnd, hIns, Mesas[5].GetState());
		Mesas[6].CreateButton(hWnd, hIns, Mesas[6].GetState());
		Mesas[7].CreateButton(hWnd, hIns, Mesas[7].GetState());
		Mesas[8].CreateButton(hWnd, hIns, Mesas[8].GetState());
		Mesas[9].CreateButton(hWnd, hIns, Mesas[9].GetState());
		Mesas[10].CreateButton(hWnd, hIns, Mesas[10].GetState());
		Mesas[11].CreateButton(hWnd, hIns, Mesas[11].GetState());
		Mesas[12].CreateButton(hWnd, hIns, Mesas[12].GetState());
		Mesas[13].CreateButton(hWnd, hIns, Mesas[13].GetState());
		Mesas[14].CreateButton(hWnd, hIns, Mesas[14].GetState());


		for (int I = 0; I < 15; I++) {
			//Esto es para desbloquear todos las mesas las cuales está a cargo el Usuario
			char BUFF[50] = { NULL };
			Mesas[I].GetInChargeUser(BUFF);
			if ((Mesas[I].GetState() == OCUPADA || Mesas[I].GetState() == EN_USO) && LoggedInUser == SearchByUser(Empleados,BUFF)) {
				EnableWindow(Mesas[I].GetHWND(),TRUE);
				TakingCare++;
			}
		}
	}
	break;
	case WM_CLOSE:
	{
		EnableWindow(GetParent(hWnd), TRUE);
		DestroyWindow(hWnd);
		if (!Extern) {
			SaveOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Ordenes.bin", &Ordenes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\OrdStuff.bin", &OrdStuff);
			SaveOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Pendientes.bin", &Pendientes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\PendStuff.bin", &PendStuff);
			SaveOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Historial.bin", &Historial, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\HistStuff.bin", &HistStuff);

			WriteTableInfo(Mesas);
			Talar(Empleados);
			Alimentos.WriteList("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Menu.bin");
			PostQuitMessage(0);
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
			{
				case MESA1:
				{
					TableSwitch(hWnd, &Mesas[0], &TakingCare);
				}
				break;
				case MESA2:
				{
					TableSwitch(hWnd, &Mesas[1], &TakingCare);
				}
				break;
				case MESA3:
				{
					TableSwitch(hWnd, &Mesas[2], &TakingCare);
				}
				break;
				case MESA4:
				{
					TableSwitch(hWnd, &Mesas[3], &TakingCare);
				}
				break;
				case MESA5:
				{
					TableSwitch(hWnd, &Mesas[4], &TakingCare);
				}
				break;
				case MESA6:
				{
					TableSwitch(hWnd, &Mesas[5], &TakingCare);
				}
				break;
				case MESA7:
				{
					TableSwitch(hWnd, &Mesas[6], &TakingCare);
				}
				break;
				case MESA8:
				{
					TableSwitch(hWnd, &Mesas[7], &TakingCare);
				}
				break;
				case MESA9:
				{
					TableSwitch(hWnd, &Mesas[8], &TakingCare);
				}
				break;
				case MESAa:
				{
					TableSwitch(hWnd, &Mesas[9], &TakingCare);
				}
				break;
				case MESAb:
				{
					TableSwitch(hWnd, &Mesas[10], &TakingCare);
				}
				break;
				case MESAc:
				{
					TableSwitch(hWnd, &Mesas[11], &TakingCare);
				}
				break;
				case MESAd:
				{
					TableSwitch(hWnd, &Mesas[12], &TakingCare);
				}
				break;
				case MESAe:
				{
					TableSwitch(hWnd, &Mesas[13], &TakingCare);
				}
				break;
				case MESAf:
				{
					TableSwitch(hWnd, &Mesas[14], &TakingCare);
				}
				break;
			}
		}
	}
	break;
	}
	return 0;
}

int EmplIDC = 30818;
int ListLastYPos = 0;
//int ButtonXSize = 200;
int ButtonYSize = 100;
SCROLLINFO ListScroll;
ListaLigada<ButtonList<Empleado*>> EmployeeButtons;
HFONT eFont = CreateFontA(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
void LoadEmployeeButtons(Empleado* Raiz, HWND Padre) {
	DWORD ButtStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE | BS_BITMAP | BS_LEFT | BS_VCENTER;
	DWORD Static = SS_LEFT | WS_TABSTOP | WS_VISIBLE | WS_CHILD;
	RECT rect;
	GetWindowRect(Padre, &rect);
	if (Raiz != 0) {
		char BUFF[300] = { NULL };
		char aux[1000] = { NULL };
		Nodo<ButtonList<Empleado*>>* NewButton = new Nodo<ButtonList<Empleado*>>();
		NewButton->Datos.SetIDC(EmplIDC);
		EmplIDC++;
		NewButton->Datos.SetButtInfo(Raiz);
		NewButton->Datos.CrearBoton(0, ListLastYPos, rect.right - rect.left, ButtonYSize, ButtStyle, Static, eFont, Padre, hIns);
		ListLastYPos += ButtonYSize + 5;
		NewButton->Datos.GetButtInfo()->GetBuff(BUFF, sizeof(BUFF));
		NewButton->Datos.SetBitmap(BUFF);
		memset(BUFF, NULL, strlen(BUFF));

		//Agregamos todo el escrito al static
		NewButton->Datos.GetButtInfo()->GetName(BUFF, sizeof(BUFF));
		strcat_s(aux, "Nombre:  ");
		strcat_s(aux, BUFF);
		memset(BUFF, NULL, strlen(BUFF));
		NewButton->Datos.GetButtInfo()->GetUser(BUFF, sizeof(BUFF));
		strcat_s(aux, "    -(");
		strcat_s(aux, BUFF);
		memset(BUFF, NULL, strlen(BUFF));
		strcat_s(aux, ")-");
		NewButton->Datos.GetButtInfo()->GetPhon(BUFF, sizeof(BUFF));
		strcat_s(aux, "\n");
		strcat_s(aux, "Telefono:  ");
		strcat_s(aux, BUFF);
		memset(BUFF, NULL, strlen(BUFF));
		NewButton->Datos.GetButtInfo()->GetMail(BUFF, sizeof(BUFF));
		strcat_s(aux, "    Correo:  ");
		strcat_s(aux, BUFF);
		memset(BUFF, NULL, strlen(BUFF));
		NewButton->Datos.SetStaticText(aux);

		EmployeeButtons.AddLast(NewButton);

		LoadEmployeeButtons(Raiz->izq, Padre);
		LoadEmployeeButtons(Raiz->der, Padre);
	}
}

BOOL CALLBACK ListProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_COMMAND:
	{
		if (wParam >= 30818) {
			if (DelEmployee) {
				bool fail = false;
				for (int I = 0; I < 15; I++) {
					char BUFF[50] = { NULL };
					Mesas[I].GetInChargeUser(BUFF);
					if (SearchByUser(Empleados,BUFF) == EmployeeButtons[(int)wParam - 30818]->Datos.GetButtInfo()) {
						fail = true;
						break;
					}
				}
				if (fail) {
					MessageBoxA(hWnd, "El empleado que trata de eliminar está a cargo de una o más mesas, no es posible continuar con la eliminación", "Error", MB_OK | MB_ICONWARNING);
				}
				else {
					int R = MessageBoxA(hWnd, "¿Seguro que desea despedir a este empleado?", "Confirmacion", MB_YESNO | MB_ICONHAND);
					if (R == IDYES) {
						Delete(Empleados, EmployeeButtons[(int)wParam - 30818]->Datos.GetButtInfo());
						EmployeeButtons.DeleteList();
						DestroyWindow(hWnd);
					}
				}
			}
			else {
				int R = MessageBoxA(hWnd, "¿Seguro que desea ingresar como empleado?", "Confirmacion", MB_YESNO | MB_ICONQUESTION);
				if (R == IDYES) {
					Extern = true;
					LoggedInUser = EmployeeButtons[(int)wParam - 30818]->Datos.GetButtInfo();
					UserWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_USUARIO), hWnd, (DLGPROC)UserProc, 0);
					ShowWindow(UserWindow, SW_SHOW);
				}
			}
		}
	}
	break;
	case WM_INITDIALOG:
	{

		ListScroll.cbSize = sizeof(SCROLLBARINFO);
		ListScroll.fMask = SIF_ALL;
		GetScrollInfo(hWnd, SB_VERT, &ListScroll);
		//Crear Botones si es que existen
		LoadEmployeeButtons(Empleados, hWnd);

	}
	break;
	case WM_VSCROLL:
	{
		GetScrollInfo(hWnd, SB_VERT, &ListScroll);
		ListScroll.cbSize = sizeof(ListScroll);
		//ListScroll.nMax = ListLastYPos + 20;
		ListScroll.nMin = 0;
		ListScroll.fMask = SIF_ALL;
		ListScroll.nPage = 50;
		ShowScrollBar(hWnd, SB_VERT, TRUE);
		switch (LOWORD(wParam))
		{
		case SB_TOP:
			ListScroll.nPos = ListScroll.nMin;
			break;

		case SB_BOTTOM:
			ListScroll.nPos = ListScroll.nMax;
			break;

		case SB_LINEUP:
			ListScroll.nPos -= 1;
			break;

		case SB_LINEDOWN:
			ListScroll.nPos += 1;
			break;

		case SB_PAGEUP:
			ListScroll.nPos -= ListScroll.nPage;
			break;

		case SB_PAGEDOWN:
			ListScroll.nPos += ListScroll.nPage;
			break;

		case SB_THUMBTRACK:
			ListScroll.nPos = ListScroll.nTrackPos;
			break;

		default:
			break;
		}
		SetScrollInfo(hWnd, SB_VERT, &ListScroll, TRUE);
		ShowScrollBar(hWnd, SB_VERT, TRUE);
		for (int K = 0; K < EmployeeButtons.Count(); K++) {
			SetWindowPos(EmployeeButtons[K]->Datos.GetHWND(), HWND_TOP, 0, EmployeeButtons[K]->Datos.Pos - ListScroll.nPos, 0, 0, SWP_NOSIZE);
		}
	}
	break;
	case WM_CLOSE:
	{
		if (!DelEmployee) {
			LoggedInUser = Admin;
			Extern = false;
		}
		ListLastYPos = 0;
		EmployeeButtons.DeleteList();
		DestroyWindow(hWnd);
	}
	break;
	default:
		break;
	}
	return 0;
}

BOOL CALLBACK PayProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_COMMAND:
	{
		switch (wParam) {
		case IDC_EFFECTIVE:
		{
			SelectedNote->Datos.SetPayment(EFECTIVO);
			DestroyWindow(hWnd);
		}
		break;
		case IDC_CARD:
		{
			SelectedNote->Datos.SetPayment(TARJETA);
			DestroyWindow(hWnd);
		}
		break;
		case IDC_PayPal:
		{
			SelectedNote->Datos.SetPayment(PAYPAL);
			DestroyWindow(hWnd);
		}
		break;
		case IDC_CUPON:
		{
			SelectedNote->Datos.SetPayment(CUPON);
			DestroyWindow(hWnd);
		}
		break;
		}
	}
	break;
	case WM_DESTROY:
	{
		OrderXChange(SelectedNote->Datos.GetFolio(), &Pendientes, &PendStuff, &Historial, &HistStuff);
		int I = SendMessage(GetDlgItem(GetParent(hWnd), IDC_PENDIENTES2), LB_GETCOUNT, NULL, NULL);
		for (int J = 0; J <= I; J++) {
			SendMessage(GetDlgItem(GetParent(hWnd), IDC_PENDIENTES2), LB_DELETESTRING, 0, NULL);
		}
		I = SendMessage(GetDlgItem(GetParent(hWnd), IDC_PENDIENTES), LB_GETCURSEL, NULL, NULL);
		SendMessage(GetDlgItem(GetParent(hWnd), IDC_PENDIENTES), LB_DELETESTRING, I, NULL);
		SelectedNote = 0;
	}
	break;
	default:
		break;
	}
	return 0;
}

BOOL CALLBACK HistorialProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_INITDIALOG:
	{
		EnableWindow(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_DATETIMEPICKER2), FALSE);

		DateInsertSort(&Historial);
		Nodo<Comienda>* Haux = Historial.head;
		while (Haux != 0) {
			char Aux[10] = { NULL };
			_itoa_s(Haux->Datos.GetFolio(), Aux, 10);
			SendMessage(GetDlgItem(hWnd, IDC_HISTO1), LB_ADDSTRING, NULL, (LPARAM)Aux);
			Haux = Haux->nxt;
		}
		Historial.CopyList(&Filtered);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDC_FILTRAR:
		{
			//Limpiamos la antigua seleccion
			int I = SendMessage(GetDlgItem(hWnd, IDC_HISTO1), LB_GETCOUNT, NULL, NULL);
			for (int J = 0; J <= I; J++) {
				SendMessage(GetDlgItem(hWnd, IDC_HISTO1), LB_DELETESTRING, 0, NULL);
			}
			I = SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_GETCOUNT, NULL, NULL);
			for (int J = 0; J <= I; J++) {
				SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_DELETESTRING, 0, NULL);
			}

			Filtered.DeleteList();
			Historial.CopyList(&Filtered);

			char USER[50] = { NULL };
			char Date1[50] = { NULL };
			char Date2[50] = { NULL };

			GetWindowText(GetDlgItem(hWnd, IDC_EMPLOYEE), USER, sizeof(USER));
			if (IsDlgButtonChecked(hWnd, IDC_CHECK1) == BST_CHECKED) {
				GetWindowText(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), Date1, sizeof(Date1));
				GetWindowText(GetDlgItem(hWnd, IDC_DATETIMEPICKER2), Date2, sizeof(Date2));
				if (strcmp(Date1, Date2) < 0) {
					DateFilter(&Filtered, Date1, Date2);
				}
				else {
					DateFilter(&Filtered, Date2, Date1);
				}
			}

			if (USER[0] != 0) {
				EmployeeFilter(&Filtered, USER);
			}
			else if(Date1[0] == 0){
				Historial.CopyList(&Filtered);
			}

			if (Filtered.head == 0) {
				MessageBoxA(hWnd, "No se encontraron coincidencias.", "Error", MB_OK | MB_ICONEXCLAMATION);
			}

			Nodo<Comienda>* Haux = Filtered.head;
			while (Haux != 0) {
				char Aux[10] = { NULL };
				_itoa_s(Haux->Datos.GetFolio(), Aux, 10);
				SendMessage(GetDlgItem(hWnd, IDC_HISTO1), LB_ADDSTRING, NULL, (LPARAM)Aux);
				Haux = Haux->nxt;
			}
		}
		break;
		case IDC_CHECK1:
		{
			if (IsDlgButtonChecked(hWnd, IDC_CHECK1) == BST_CHECKED) {
				EnableWindow(GetDlgItem(hWnd, IDC_DATETIMEPICKER1),TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_DATETIMEPICKER2), TRUE);
			}
			else {
				EnableWindow(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_DATETIMEPICKER2), FALSE);
			}
		}
		break;
		}
		switch (HIWORD(wParam)) {
		case LBN_SELCHANGE:
		{
			switch (LOWORD(wParam)) {
			case IDC_HISTO1:
			{
				//Limpiamos la antigua seleccion
				int I = SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_GETCOUNT, NULL, NULL);
				for (int J = 0; J <= I; J++) {
					SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_DELETESTRING, 0, NULL);
				}
				I = SendMessage(GetDlgItem(hWnd, IDC_HISTO1), LB_GETCURSEL, NULL, NULL);

				char DIR[500] = { NULL };
				char AUX[50] = { NULL };
				char FAUX[10] = { NULL };
				SendMessage(GetDlgItem(hWnd, IDC_HISTO1), LB_GETTEXT, I, (LPARAM)FAUX);
				//Ahora ya escribimos el archivo
				Mesas[Filtered[I]->Datos.GetTableNumber() - 1].GetInChargeUser(AUX);
				SelectedNote = SearchOrderByFolio(&Filtered, atoi(FAUX));
				int K = SelectedNote->Datos.GetClientNum();
				float Sum = 0.0;
				strcat_s(DIR, AUX);
				strcat_s(DIR, "     ");
				tm* Date = SelectedNote->Datos.GetDate();
				memset(AUX, NULL, strlen(AUX));
				_itoa_s(Date->tm_mday,AUX,10);
				strcat_s(DIR,AUX);
				strcat_s(DIR, "/");
				memset(AUX, NULL, strlen(AUX));
				_itoa_s(Date->tm_mon + 1, AUX, 10);
				strcat_s(DIR, AUX);
				strcat_s(DIR, "/");
				memset(AUX, NULL, strlen(AUX));
				_itoa_s(Date->tm_year + 1900, AUX, 10);
				strcat_s(DIR, AUX);
				SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_ADDSTRING, NULL, (LPARAM)DIR);
				for (int G = 0; G < K; G++) {
					memset(DIR, NULL, strlen(DIR));
					memset(AUX, NULL, strlen(AUX));
					strcat_s(DIR, "Cliente ");
					_itoa_s(G + 1, AUX, 10);
					strcat_s(DIR, AUX);
					SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_ADDSTRING, NULL, (LPARAM)DIR);
					Nodo<Stuff> *caux;
					float CT = 0.0;
					for (caux = SearchStuffByFolio(&HistStuff, atoi(FAUX)); caux != 0; caux = caux->nxt) {
						if (caux->Datos.Folio != atoi(FAUX)) {
							break;
						}
						memset(DIR, NULL, strlen(DIR));
						memset(AUX, NULL, strlen(AUX));
						if (caux->Datos.ClientNum == G) {
							strcat_s(DIR, "   ");
							SearchFoodByID(&Alimentos, caux->Datos.FoodID)->Datos.GetName(&DIR[3], 100);
							strcat_s(DIR, "   $");
							sprintf_s(AUX, "%.2f", caux->Datos.FoodPrice);
							strcat_s(DIR, AUX);
							CT += caux->Datos.FoodPrice;
							SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_ADDSTRING, NULL, (LPARAM)DIR);
						}
					}
					memset(DIR, NULL, strlen(DIR));
					memset(AUX, NULL, strlen(AUX));

					strcat_s(DIR, "       total del cliente ");
					_itoa_s(G + 1, AUX, 10);
					strcat_s(DIR, AUX);
					strcat_s(DIR, "   $");
					memset(AUX, NULL, strlen(AUX));
					sprintf_s(AUX, "%.2f", CT);
					strcat_s(DIR, AUX);

					SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_ADDSTRING, NULL, (LPARAM)DIR);
					Sum = Sum + CT;
				}
				memset(DIR, NULL, strlen(DIR));
				memset(AUX, NULL, strlen(AUX));
				strcat_s(DIR, "    total sin propina   $");
				sprintf_s(AUX, "%.2f", Sum);
				strcat_s(DIR, AUX);
				SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_ADDSTRING, NULL, (LPARAM)DIR);

				memset(DIR, NULL, strlen(DIR));
				memset(AUX, NULL, strlen(AUX));
				strcat_s(DIR, "    TOTAL   $");
				sprintf_s(AUX, "%.2f", Sum * (1 + Historial[I]->Datos.GetTip()));
				strcat_s(DIR, AUX);
				SendMessage(GetDlgItem(hWnd, IDC_HISTO2), LB_ADDSTRING, NULL, (LPARAM)DIR);
			}
			break;
			}
		}
		break;
		default:
			break;
		}

	}
	break;
	case WM_CLOSE:
	{
		Filtered.DeleteList();
		DestroyWindow(hWnd);
	}
	break;
	default:
		break;
	}
	return 0;
}

BOOL CALLBACK ConsulProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_INITDIALOG:
	{
		//Cargamos el ComboBox
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Postre");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Bebida");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Desayuno");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Comida");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Cena");
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDC_FILTRAR:
		{
			int I = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCOUNT, NULL, NULL);
			for (int J = 0; J <= I; J++) {
				SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_DELETESTRING, 0, NULL);
			}
			char Category[20] = { NULL };
			comida Cat;
			bool error = false;
			GetWindowText(GetDlgItem(hWnd, IDC_CATEGORIA), Category, sizeof(Category));
			if (Category[0] == NULL) {
				MessageBoxA(hWnd, "Seleccione una categoria primero.", "Error", MB_OK | MB_ICONEXCLAMATION);
				error = true;
			}
			else if (strcmp(Category, "Postre") == 0) {
				Cat = POSTRE;
			}
			else if (strcmp(Category, "Bebida") == 0) {
				Cat = BEBIDA;
			}
			else if (strcmp(Category, "Desayuno") == 0) {
				Cat = DESAYUNO;
			}
			else if (strcmp(Category, "Comida") == 0) {
				Cat = COMIDA;
			}
			else if (strcmp(Category, "Cena") == 0) {
				Cat = CENA;
			}
			Nodo<Stuff>* Staux = HistStuff.head;
			while (Staux != 0 && !error) {
				Nodo<Alimento>* Food = SearchFoodByID(&Alimentos, Staux->Datos.FoodID);
				if (Food->Datos.GetCategory() == Cat) {
					char AUX[100] = { NULL };
					Food->Datos.GetName(AUX, sizeof(AUX));
					char faux[10] = { NULL };
					sprintf_s(faux, "%.2f", Staux->Datos.FoodPrice);
					strcat_s(AUX, "   $");
					strcat_s(AUX, faux);
					memset(faux, NULL, strlen(faux));
					strcat_s(AUX, "   Folio: ");
					_itoa_s(Staux->Datos.FoodID, faux, 10);
					strcat_s(AUX, faux);
					SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_ADDSTRING, NULL, (LPARAM)AUX);
				}
				Staux = Staux->nxt;
			}
		}
		break;
		}
	}
	break;
	}
	return 0;
}

BOOL CALLBACK AdminProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
	{
		EditFood = false;
		DelFood = false;
		DelEmployee = false;
		//LeerArchivoBinEmpleados(Empleados);
		ReadTableInfo(Mesas);
		LoadOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Ordenes.bin", &Ordenes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\OrdStuff.bin", &OrdStuff);
		LoadOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Pendientes.bin", &Pendientes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\PendStuff.bin", &PendStuff);
		LoadOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Historial.bin", &Historial, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\HistStuff.bin", &HistStuff);
		//Cargamos en la primer List Box el texto de las pendientes

		Nodo<Comienda>* Paux = Pendientes.head;
		while (Paux != 0) {
			char Aux[10] = { NULL };
			_itoa_s(Paux->Datos.GetFolio(), Aux, 10);
			SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES), LB_ADDSTRING, NULL, (LPARAM)Aux);
			Paux = Paux->nxt;
		}

	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
			case ID_MESEROS_NUEVOMESERO:
			{
				AddUserWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_AGREMPLE), hWnd, (DLGPROC)AddUserProc, 0);
				ShowWindow(AddUserWindow, SW_SHOW);
			}
			break;
			case ID_MESEROS_DESPEDIRMESERO:
			{
				DelEmployee = true;
				ListWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_LIST), hWnd, (DLGPROC)ListProc, 0);
				ShowWindow(ListWindow, SW_SHOW);
			}
			break;
			case ID_MESEROS_ACCEDERCOMOMESERO:
			{
				ListWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_LIST), hWnd, (DLGPROC)ListProc, 0);
				ShowWindow(ListWindow, SW_SHOW);
			}
			break;
			case ID_PLATILLOS_AGREGAR:
			{
				if (Ordenes.head == 0) {
					AddFoodWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_AGREALIM), hWnd, (DLGPROC)AddFoodProc, 0);
					ShowWindow(AddFoodWindow, SW_SHOW);
				}
				else {
					MessageBoxA(hWnd, "Hay ordenes activas por el momento, no se debe modificar el menu por el momento.", "Error", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			break;
			case ID_PLATILLOS_EDITAR:
			{
				if (Ordenes.head == 0) {
					EditFood = true;
					SelectorWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_SELECTOR), hWnd, (DLGPROC)SelectorProc, 0);
					ShowWindow(SelectorWindow, SW_SHOW);
				}
				else {
					MessageBoxA(hWnd, "Hay ordenes activas por el momento, no se debe modificar el menu por el momento.", "Error", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			break;
			case ID_PLATILLOS_ELIMINAR:
			{
				if (Ordenes.head == 0) {
					DelFood = true;
					SelectorWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_SELECTOR), hWnd, (DLGPROC)SelectorProc, 0);
					ShowWindow(SelectorWindow, SW_SHOW);
				}
				else {
					MessageBoxA(hWnd, "Hay ordenes activas por el momento, no se deben eliminar elementos por el momento.", "Error", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			break;
			case ID_ADMINISTRAR_FINALIZARDIA:
			{
				if (Ordenes.head == 0) {
					Mesas[0].SetState(LIBRE);
					Mesas[1].SetState(LIBRE);
					Mesas[2].SetState(LIBRE);
					Mesas[3].SetState(LIBRE);
					Mesas[4].SetState(LIBRE);
					Mesas[5].SetState(LIBRE);
					Mesas[6].SetState(LIBRE);
					Mesas[7].SetState(LIBRE);
					Mesas[8].SetState(LIBRE);
					Mesas[9].SetState(LIBRE);
					Mesas[10].SetState(LIBRE);
					Mesas[11].SetState(LIBRE);
					Mesas[12].SetState(LIBRE);
					Mesas[13].SetState(LIBRE);
					Mesas[14].SetState(LIBRE);
				}
				else {
					MessageBoxA(hWnd, "Hay ordenes activas por el momento, no se puede terminar el dia", "Error", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			break;
			case ID_HISTORIAL_CUENTAS:
			{
				HistorialWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_HISTORIAL), hWnd, (DLGPROC)HistorialProc, 0);
				ShowWindow(HistorialWindow, SW_SHOW);
			}
			break;
			case ID_VENTAS_PLATILLOSPORCATEGORIA:
			{
				ConsulWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_CONSUL), hWnd, (DLGPROC)ConsulProc, 0);
				ShowWindow(ConsulWindow, SW_SHOW);
			}
			break;
			case IDOK:
			{
				//Aquí se "paga" el nodo seleccionado de Pendientes y la manda a Historial.
				int I = SendMessage(GetDlgItem(hWnd,IDC_PENDIENTES),LB_GETCURSEL,NULL,NULL);
				if(I != LB_ERR){
					PayWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_PAYMENT), hWnd, (DLGPROC)PayProc, 0);
					ShowWindow(PayWindow, SW_SHOW);
				}
				else {
					//Mensaje
					MessageBoxA(hWnd, "Primero seleccione una cuenta para llevar a cabo esta acción", "Notificacion", MB_OK | MB_ICONHAND);
				}
			}
			break;
		}
		switch (HIWORD(wParam)) {
		case LBN_SELCHANGE:
		{
			switch (LOWORD(wParam)) {
			case IDC_PENDIENTES:
			{
				//Limpiamos la antigua seleccion
				int I = SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_GETCOUNT, NULL, NULL);
				for (int J = 0; J <= I; J++) {
					SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_DELETESTRING, 0, NULL);
				}
				I = SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES), LB_GETCURSEL, NULL, NULL);
				
				char DIR[500] = { NULL };
				char AUX[50] = { NULL };
				char FAUX[10] = { NULL };
				SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES), LB_GETTEXT, I, (LPARAM)FAUX);
				//Ahora ya escribimos el archivo
				Mesas[Pendientes[I]->Datos.GetTableNumber() - 1].GetInChargeUser(AUX);
				SelectedNote = SearchOrderByFolio(&Pendientes, atoi(FAUX));
				int K = SelectedNote->Datos.GetClientNum();
				float Sum = 0.0;
				SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_ADDSTRING,NULL, (LPARAM)AUX);
				for (int G = 0; G < K; G++) {
					memset(DIR, NULL, strlen(DIR));
					memset(AUX, NULL, strlen(AUX));
					strcat_s(DIR, "Cliente ");
					_itoa_s(G + 1, AUX, 10);
					strcat_s(DIR, AUX);
					SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_ADDSTRING, NULL, (LPARAM)DIR);
					Nodo<Stuff> *caux;
					float CT = 0.0;
					for (caux = SearchStuffByFolio(&PendStuff,atoi(FAUX));  caux != 0; caux = caux->nxt) {
						if (caux->Datos.Folio != atoi(FAUX)) {
							break;
						}
						memset(DIR, NULL, strlen(DIR));
						memset(AUX, NULL, strlen(AUX));
						if (caux->Datos.ClientNum == G) {
							strcat_s(DIR, "   ");
							SearchFoodByID(&Alimentos, caux->Datos.FoodID)->Datos.GetName(&DIR[3], 100);
							strcat_s(DIR, "   $");
							sprintf_s(AUX, "%.2f", caux->Datos.FoodPrice);
							strcat_s(DIR, AUX);
							CT += caux->Datos.FoodPrice;
							SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_ADDSTRING, NULL, (LPARAM)DIR);
						}
					}
					memset(DIR, NULL, strlen(DIR));
					memset(AUX, NULL, strlen(AUX));

					strcat_s(DIR, "       total del cliente ");
					_itoa_s(G + 1, AUX, 10);
					strcat_s(DIR, AUX);
					strcat_s(DIR, "   $");
					memset(AUX, NULL, strlen(AUX));
					sprintf_s(AUX, "%.2f", CT);
					strcat_s(DIR, AUX);
		
					SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_ADDSTRING, NULL, (LPARAM)DIR);
					Sum = Sum + CT;
				}
				memset(DIR, NULL, strlen(DIR));
				memset(AUX, NULL, strlen(AUX));
				strcat_s(DIR, "    total sin propina   $");
				sprintf_s(AUX, "%.2f", Sum);
				strcat_s(DIR, AUX);
				SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_ADDSTRING, NULL, (LPARAM)DIR);

				memset(DIR, NULL, strlen(DIR));
				memset(AUX, NULL, strlen(AUX));
				strcat_s(DIR, "    TOTAL   $");
				sprintf_s(AUX, "%.2f", Sum * (1 + Pendientes[I]->Datos.GetTip()));
				strcat_s(DIR, AUX);
				SendMessage(GetDlgItem(hWnd, IDC_PENDIENTES2), LB_ADDSTRING, NULL, (LPARAM)DIR);
			}
			break;
			}
		}
		break;
		default:
			break;
		}

	}
	break;
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		WriteTableInfo(Mesas);
		EscribirEnArchivoBinEmpleados(Empleados);
		SaveOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Ordenes.bin", &Ordenes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\OrdStuff.bin", &OrdStuff);
		SaveOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Pendientes.bin", &Pendientes, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\PendStuff.bin", &PendStuff);
		SaveOrders("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Historial.bin", &Historial, "C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\HistStuff.bin", &HistStuff);
		Talar(Empleados);
		Alimentos.WriteList("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Menu.bin");
		PostQuitMessage(0);
	}
	break;

	}
	return 0;
}

BOOL CALLBACK LogInProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static char User[50] = { NULL };
	static char Pass[50] = { NULL };

	switch (msg) {
	case WM_INITDIALOG:
	{
		ifstream in("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Admin.txt", ios::in);
		in.seekg(0, in.beg);
		in.getline(AdminUser, sizeof(AdminUser));
		in.getline(AdminPass, sizeof(AdminPass));
		Admin->SetUser(AdminUser);
		Admin->SetPass(AdminPass);

		LeerArchivoBinEmpleados(Empleados);
		Alimentos.ReadList("C:\\Users\\gabri\\source\\repos\\ProyectoEstDDat\\ProyectoEstDDat\\Info\\Menu.bin");
	}
	break;
	case WM_COMMAND:
	{
		switch (wParam) {
		case IDCANCEL:
		{
			DestroyWindow(hWnd);
			Talar(Empleados);
			PostQuitMessage(0);
		}
		break;
		case IDOK:
		{
			GetWindowText(GetDlgItem(hWnd, IDC_USUARIO), User, sizeof(User));
			GetWindowText(GetDlgItem(hWnd, IDC_CONTRASENA), Pass, sizeof(Pass));
			LoggedInUser = LogIn(Empleados, User, Pass);
			if (LoggedInUser == 0) {
				//Mensaje de Error
				MessageBoxA(hWnd, "El usuario o contraseña no se encuentran en los registros", "Acceso Denegado", MB_OK | MB_ICONHAND);
				break;

			}
			else if (LoggedInUser == Admin) {
				//Ingreso de Admin
				AdminWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_ADMIN), 0, (DLGPROC)AdminProc, 0);
				ShowWindow(AdminWindow, SW_SHOW);
				DestroyWindow(hWnd);
			}
			else {
				//Ingreso de Usuario ID
				UserWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_USUARIO), 0, (DLGPROC)UserProc, 0);
				ShowWindow(UserWindow, SW_SHOW);
				DestroyWindow(hWnd);
			}
		}
		break;
		}
	}
	break;
	case WM_CLOSE:
	{
			DestroyWindow(hWnd);
			Talar(Empleados);
			PostQuitMessage(0);
	}
	break;
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int nShowCmd) {

	MSG msg;
	hIns = hInst;

	LogInWindow = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_INGRESO), 0, (DLGPROC)LogInProc, 0);
	ShowWindow(LogInWindow, nShowCmd);

	//UserWindow = CreateDialogParam(hIns, MAKEINTRESOURCE(IDD_USUARIO), 0, (DLGPROC)UserProc, 0);
	//ShowWindow(UserWindow, nShowCmd);
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}