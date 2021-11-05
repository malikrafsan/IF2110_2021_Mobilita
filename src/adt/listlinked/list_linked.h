/* File : list_linked.h */
/* contoh ADT ListLinked berkait dengan representasi fisik pointer  */
/* Representasi Address dengan pointer */

#ifndef ListLinked_LINKED_H
#define ListLinked_LINKED_H

#include "../../include/constants.h"
#include "../../include/boolean.h"
#include "node.h"

#define LISTLINKED_CAPACITY TASK_CAP
typedef Address ListLinked;

#define FIRST(l) (l)

/* Definisi ListLinked : */
/* ListLinked kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir ListLinked: jika addressnya Last, maka NEXT(Last)=NULL */

/* PROTOTYPE */
/****************** PEMBUATAN ListLinked KOSONG ******************/
void CreateListLinked(ListLinked *l);
/* I.S. sembarang             */
/* F.S. Terbentuk ListLinked kosong */

/****************** TEST ListLinked KOSONG ******************/
boolean isEmptyListLinked(ListLinked l);
/* Mengirim true jika ListLinked kosong */

/****************** GETTER SETTER ******************/
ElTypeListLinked getElmtListLinked(ListLinked l, int idx);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..lengthListLinked(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */

void setElmtListLinked(ListLinked *l, int idx, ElTypeListLinked val);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..lengthListLinked(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

int indexOfListLinked(ListLinked l, ElTypeListLinked val);
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen ListLinked l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak dElTypeListLinkedukan */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstListLinked(ListLinked *l, ElTypeListLinked val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */

void insertLastListLinked(ListLinked *l, ElTypeListLinked val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListLinked di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteLastListLinked(ListLinked *l, ElTypeListLinked *val);
/* I.S. ListLinked tidak kosong */
/* F.S. Elemen terakhir ListLinked dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PROSES SEMUA ELEMEN ListLinked ******************/
int lengthListLinked(ListLinked l);
/* Mengirimkan banyaknya elemen ListLinked; mengirimkan 0 jika ListLinked kosong */

/****************** PROSES TERHADAP ListLinked ******************/
ListLinked concatListLinked(ListLinked l1, ListLinked l2);
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah ListLinked : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen ListLinked l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */

#endif