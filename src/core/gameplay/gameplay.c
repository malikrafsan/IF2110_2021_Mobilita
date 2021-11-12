#include "gameplay.h"
#include "../../include/wrapper.h"
#include "../../object/ability/ability.h"


void doMovePlayer()
{
    if (navigateAndMoveMobita(false)) {
        advanceTime();
        updateGame();
        // Move every item that has pickup time larger than current time.
        // Do it after updateGame() to make sure item perishable is updated correctly.
        Item* temp;
        while (!isEmptyQueue(GTASK) && (QUEUE_HEAD(GTASK)->timePickUp <= GTIME.currentTime)) {
            dequeue(&GTASK, &temp);
            // It's possible that deltaTime was larger, so we need to properly update this
            if (temp->type == PERISHABLE) {
                temp->currentDuration -= GTIME.currentTime - temp->timePickUp;
            }
            insertLastListLinked(&GSTATS.toDoList, temp);
        }
    }
}

void doPickUp()
// Put getPickUpItem into the bag
{
    Item *item = getPickUpItem(), *temp;
    if (item == NULL) {
        printf("Tidak ada pesanan yang dapat diambil pada bangunan ini.\n");
    } else {
        if (lengthListLinked(GSTATS.inProgressList) == GSTATS.bagCapEff) {
            printf("Tas sudah penuh, silahkan drop off barang terlebih dahulu\n");
        } else if (toDoListHas(VIP) && item->type != VIP) {
            printf("Ambil item VIP terlebih dahulu!\n");
        } else {
            push(&GSTATS.bag, item);
            insertLastListLinked(&GSTATS.inProgressList, item);
            printf(
                "Pesanan berupa %s berhasil diambil!\nTujuan Pesanan: %c\n",
                getItemTypeName(item->type),
                item->dropOff->letter
            );
            if (GSTATS.speedBoostDuration > 0 && item->type == HEAVY)
                removeAbility(SPEED_BOOST);
            int idx = indexOfListLinked(GSTATS.toDoList, item);
            deleteAtListLinked(&GSTATS.toDoList, idx, &temp);
        }
    }
}
void doDropOff() 
// Pop bag and remove currentItem in progress list
{
    Item *item = getCurrentItem(), *temp;
    if (item == NULL) {
        printf("Tidak ada item pada bag.\n");
    } else if (item->dropOff == MOBITAPOS){
        pop(&GSTATS.bag, &temp);
        deleteLastListLinked(&GSTATS.inProgressList, &temp);
        if (GSTATS.senterPengecil) {
            GSTATS.senterPengecil = false;
            printf("Senter pengecil habis karena item sudah di drop off.\n");
        }
        GSTATS.totalDeliveredItem++;
        switch(item->type) {
            case NORMAL:
                GSTATS.money += 200;
                printf("Pesanan Normal Item berhasil diantarkan\nUang yang didapatkan: 200 Yen\n");
                break;
            case HEAVY:
                GSTATS.money += 400;
                printf("Pesanan Heavy Item berhasil diantarkan\nUang yang didapatkan: 400 Yen\n");
                if (inProgressListHas(HEAVY)) {
                    printf("Ability SPEED BOOST gagal diaktifkan karena ada HEAVY item di tas mobita.\n");
                } else {
                    addAbility(SPEED_BOOST);
                    printf("Mendapatkan ability SPEED BOOST!\n");
                }
                break;
            case PERISHABLE:
                GSTATS.money += 400;
                printf("Pesanan Perishable Item berhasil diantarkan\nUang yang didapatkan: 400 Yen\n");
                if (GSTATS.bagCapEff >= BAG_CAP) {
                    printf("Bag capacity boost gagal diaktifkan karena tas sudah penuh.\n");
                } else {
                    applyAbility(INCREASE_CAPACITY);
                    printf("Mendapatkan Increase Capacity pada bag.\n");
                }
                break;
            case VIP:
                GSTATS.money += 600;
                printf("Pesanan VIP Item berhasil diantarkan\nUang yang didapatkan: 600 Yen\nMendapatkan ability RETURN TO SENDER!\n");
                addAbility(RETURN_TO_SENDER);
                break;
        }
        free(item);
    } else {
        printf("Tidak ada pesanan yang dapat diantarkan di bangunan ini!\n");
    }
}

int countTimeAddition(){
    int count = 1;
    // Traversal heavy item di inProgressList
    Item *item = getCurrentItem();
    Address p = FIRST(GSTATS.inProgressList);
    while (p != NULL){
        if (INFO(p)->type == HEAVY)
            if ((GSTATS.senterPengecil && INFO(p) != item) || !GSTATS.senterPengecil)
                count++;
        p = NEXT(p);
    }
    return count;
}

void checkEndGame() {
    if (GSTATS.totalDeliveredItem + GSTATS.totalFailedItem == GAME.totalTask) {
        printf("Kamu berhasil, Mobita!\n");
        printf("XXXX== Statistik Permainan ==XXXX\n");
        printf("Total item yang berhasil Mobita kirim: %d\n", GSTATS.totalDeliveredItem);
        printf("Total item yang gagal Mobita kirim: %d\n", GSTATS.totalFailedItem);
        printf("Total item yang dapat dikerjakan Mobita: %d\n", GAME.totalTask);
        printf("Total waktu yang dibutuhkan Mobita: %d\n", GTIME.currentTime);
        printf("=================================\n");
        printf("Terimakasih telah bermain ^o^\n");
        exit(0);
    }
}
