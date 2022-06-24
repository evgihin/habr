#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
/*Список ключей для вставки*/
static char *data[] = { "alpha", "bravo", "charlie", "delta",
     "echo", "foxtrot", "golf", "hotel", "india", "juliet",
     "kilo", "lima", "mike", "november", "oscar", "papa",
     "quebec", "romeo", "sierra", "tango", "uniform",
     "victor", "whisky", "x-ray", "yankee", "zulu"
};
	int fd;
	void *addr;
  	int offset;
 	int size; /*Размер таблицы*/
 	int elm; /*Количество записей*/

/*Первый аргумент программы нужно указать фаил для вставки в память*/	
int main(int argc, char *argv[])
{
	addr = NULL;
	size = 256;
	offset = 0;
	elm = 30;
  	fd = open(argv[1], O_RDWR);
    ENTRY e;
    ENTRY *ep[elm]; 
    hcreate(elm);
  	/*Инициализация, вставка и размещение в общей памяти таблицы*/
    for (long int i = 0; i < 24; i++) {
        ep[i] = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
		offset += size + 1;
        e.key = data[i];
        e.data = (void *) i;
        ep[i] = hsearch(e, ENTER);/*Добавить редактирование, дефрагментацию*/
    }
	/*Чтение таблиц*/
    for (long int i = 0; i < 23; i++) {
        e.key = data[i];
        ep[i] = hsearch(e, FIND);
		printf("%s -> %ld\n", ep[i]->key, (long int)(ep[i]->data));
    }
    hdestroy();
}
/*
Отсутствуют функция мониторинга памяти
Код не оптимизирован и не покрыт тестами
*/