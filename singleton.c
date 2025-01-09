#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Определение структуры для одиночки
typedef struct {
    int value;
} Singleton;

// Глобальная переменная для хранения экземпляра
static Singleton* instance = NULL;

// Мьютекс для синхронизации доступа
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Функция для получения экземпляра одиночки
Singleton* get_instance() {
    // Двойная проверка блокировки (Double Checked Locking)
    if (instance == NULL) {
        // Блокировка мьютекса
        pthread_mutex_lock(&mutex);
        
        if (instance == NULL) {
            instance = (Singleton*)malloc(sizeof(Singleton));
            if (instance == NULL) {
                perror("Ошибка выделения памяти");
                pthread_mutex_unlock(&mutex);
                return NULL;
            }
            instance->value = 42; // Инициализируем значение
        }
        
        // Разблокировка мьютекса
        pthread_mutex_unlock(&mutex);
    }
    return instance;
}

// Функция для освобождения ресурсов
void destroy_instance() {
    if (instance != NULL) {
        // Блокировка мьютекса
        pthread_mutex_lock(&mutex);
        
        free(instance);
        instance = NULL;
        
        // Разблокировка мьютекса
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
	Singleton* singleton1 = get_instance();
	Singleton* singleton2 = get_instance();
	
	if (singleton1 == singleton2) {
	    printf("Успешно создан синглтон!\n");
	} else {
	    printf("Не удалось создать синглтон.\n");
	}

    destroy_instance(); // Освобождаем ресурсы перед завершением программы
    
    return 0;
}

