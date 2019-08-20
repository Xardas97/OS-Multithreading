#include"SemList.h"

SemaphoreList::SemaphoreList(){
	prvi = 0;
}

int SemaphoreList::put(KernelSem* newSem){
	int newId = -1;
	for(int i=0; i<30; i++) //trazimo mesta u nizu
		if(semArray[i] == 0){
			semArray[i] = newSem;
			newId = i;
			break;
		}
	if(newId == -1){ //nismo nasli u nizu
		elem *novi = new elem(); //pravimo novi element za listu
		novi->sem = newSem;

		newId = 30; //prvi indeks u listi
		elem *tek, *pret=0;
		for(tek = prvi; tek; pret = tek, tek=tek->sled) //trazimo mesta u listi
			if(newId != tek->id) break; //nasli smo u listi
			else newId++;

		if(pret) pret->sled = novi;
		else prvi = novi;

		if(tek) //ako smo nasli prostora u listi
			novi->sled = tek;
		else //nismo nasli prostora u listi;
			novi->sled = 0;
		novi->id = newId;
	}
	return newId;
}

KernelSem* SemaphoreList::get(int id){
	if(id<0) return 0; //negativan indeks nije dozvoljen
	if(id<30) return semArray[id]; //indeks pripada nizu

	for(elem *tek=prvi; tek; tek=tek->sled){ //trazimo u listi
		if(tek->id == id) return tek->sem; //nasli smo u listi
		if(tek->id > id) break; //presli smo deo u listi gde bi se on nalazio
	}
	return 0; //nismo nasli nista
}

void SemaphoreList::remove(int id){
	if(id<0) return;
	KernelSem* toDelete = 0;

	if(id<30){ //trazimo u nizu
		toDelete = semArray[id];
		semArray[id] = 0;
	}

	elem *tek, *pret = 0;
	for(tek=prvi; tek; pret=tek, tek=tek->sled){ //trazimo u listi
		if(tek->id == id){
			toDelete = tek->sem;
			break;
		}
	}
	if(tek){ //nasli smo ga
		if(pret) pret->sled = tek->sled;
		else prvi = tek->sled;
		delete tek;
	}

	if(toDelete) delete toDelete;
}
