/*
 * 
 *  Sandpiles Implemented /w Hash Table 0.1
 *  Copyright (C) 2018 Manny Peterson <me@mannypeterson.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define HASH_CODE(x, y) (10000 * x) + y
#define HASH_TABLE_SIZE 10000

struct HashTableEntry {
    int hashCode;
    int x;
    int y;
    int value;
};

struct HashTableEntry *hashTable;
int highWaterMark = 0;

int main(int argc, char *argv[]) {
    int stablePasses, leftHashCodeFound, rightHashCodeFound, topHashCodeFound, bottomHashCodeFound, i = 0, j = 0;
    struct HashTableEntry *leftHashTableEntry, *rightHashTableEntry, *topHashTableEntry, *bottomHashTableEntry;
 
    hashTable = (struct HashTableEntry *) malloc(HASH_TABLE_SIZE * sizeof(struct HashTableEntry));
    memset(hashTable, 0, HASH_TABLE_SIZE * sizeof(struct HashTableEntry));
    leftHashTableEntry = (struct HashTableEntry *) malloc(sizeof(struct HashTableEntry));
    memset(leftHashTableEntry, 0, sizeof(struct HashTableEntry));
    rightHashTableEntry = (struct HashTableEntry *) malloc(sizeof(struct HashTableEntry));
    memset(rightHashTableEntry, 0, sizeof(struct HashTableEntry));
    topHashTableEntry = (struct HashTableEntry *) malloc(sizeof(struct HashTableEntry));
    memset(topHashTableEntry, 0, sizeof(struct HashTableEntry));
    bottomHashTableEntry = (struct HashTableEntry *) malloc(sizeof(struct HashTableEntry));
    memset(bottomHashTableEntry, 0, sizeof(struct HashTableEntry));

    (hashTable + highWaterMark)->x = 500;
    (hashTable + highWaterMark)->y = 500;
    (hashTable + highWaterMark)->value = 10000;
    (hashTable + highWaterMark)->hashCode = HASH_CODE((hashTable + highWaterMark)->x, (hashTable + highWaterMark)->y);
    highWaterMark++;
    
    while (1) {
        if((hashTable + i)->value > 3) {
            stablePasses = 0;
            (hashTable + i)->value -= 4;
            
            leftHashTableEntry->x = (hashTable + i)->x - 1;
            leftHashTableEntry->y = (hashTable + i)->y;
            leftHashTableEntry->hashCode = HASH_CODE(leftHashTableEntry->x, leftHashTableEntry->y);
            leftHashCodeFound = FALSE;

            rightHashTableEntry->x = (hashTable + i)->x + 1;
            rightHashTableEntry->y = (hashTable + i)->y;
            rightHashTableEntry->hashCode = HASH_CODE(rightHashTableEntry->x, rightHashTableEntry->y);
            rightHashCodeFound = FALSE;

            topHashTableEntry->x = (hashTable + i)->x;
            topHashTableEntry->y = (hashTable + i)->y - 1;
            topHashTableEntry->hashCode = HASH_CODE(topHashTableEntry->x, topHashTableEntry->y);
            topHashCodeFound = FALSE;

            bottomHashTableEntry->x = (hashTable + i)->x;
            bottomHashTableEntry->y = (hashTable + i)->y + 1;
            bottomHashTableEntry->hashCode = HASH_CODE(bottomHashTableEntry->x, bottomHashTableEntry->y);
            bottomHashCodeFound = FALSE;

            for(j = 0; j < highWaterMark; j++) {
                if((hashTable + j)->hashCode == leftHashTableEntry->hashCode) {
                    (hashTable + j)->value++;
                    leftHashCodeFound = TRUE;
                } else if((hashTable + j)->hashCode == rightHashTableEntry->hashCode) {
                    (hashTable + j)->value++;
                    rightHashCodeFound = TRUE;
                } else if((hashTable + j)->hashCode == topHashTableEntry->hashCode) {
                    (hashTable + j)->value++;
                    topHashCodeFound = TRUE;
                } else if((hashTable + j)->hashCode == bottomHashTableEntry->hashCode) {
                    (hashTable + j)->value++;
                    bottomHashCodeFound = TRUE;
                }
            }
        
            if(!leftHashCodeFound) {
                (hashTable + highWaterMark)->x = leftHashTableEntry->x;
                (hashTable + highWaterMark)->y = leftHashTableEntry->y;
                (hashTable + highWaterMark)->value = 1;
                (hashTable + highWaterMark)->hashCode = leftHashTableEntry->hashCode;
                highWaterMark++;
            }
            if(!rightHashCodeFound) {
                (hashTable + highWaterMark)->x = rightHashTableEntry->x;
                (hashTable + highWaterMark)->y = rightHashTableEntry->y;
                (hashTable + highWaterMark)->value = 1;
                (hashTable + highWaterMark)->hashCode = rightHashTableEntry->hashCode;
                highWaterMark++;
            }
            if(!topHashCodeFound) {
                (hashTable + highWaterMark)->x = topHashTableEntry->x;
                (hashTable + highWaterMark)->y = topHashTableEntry->y;
                (hashTable + highWaterMark)->value = 1;
                (hashTable + highWaterMark)->hashCode = topHashTableEntry->hashCode;
                highWaterMark++;
            }
            if(!bottomHashCodeFound) {
                (hashTable + highWaterMark)->x = bottomHashTableEntry->x;
                (hashTable + highWaterMark)->y = bottomHashTableEntry->y;
                (hashTable + highWaterMark)->value = 1;
                (hashTable + highWaterMark)->hashCode = bottomHashTableEntry->hashCode;
                highWaterMark++;            
            }
        }

        i++;

        if(i == highWaterMark) {
            i = 0;
            stablePasses++;
            if(stablePasses > 1) {
                printf("%5d STABLE PASSES!\n", stablePasses);
                break;
            }
        }
    }
    
    return(0);    
}
