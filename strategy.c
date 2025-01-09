#include <stdio.h>
#include <stdlib.h>

// Абстрактный интерфейс стратегии
typedef struct StrategyVTable {
    double (*calculate)(double a, double b);
} StrategyVTable;

typedef struct Strategy {
    const StrategyVTable* vtable;
} Strategy;

// Конкретные реализации стратегий
typedef struct AdditionStrategy {
    const StrategyVTable* vtable;
} AdditionStrategy;

typedef struct SubtractionStrategy {
    const StrategyVTable* vtable;
} SubtractionStrategy;

typedef struct MultiplicationStrategy {
    const StrategyVTable* vtable;
} MultiplicationStrategy;

// Методы для каждой стратегии
double addition(double a, double b) {
    return a + b;
}

double subtraction(double a, double b) {
    return a - b;
}

double multiplication(double a, double b) {
    return a * b;
}

// Таблицы виртуальных методов для каждой стратегии
const StrategyVTable ADDITION_VTABLE = { .calculate = addition };
const StrategyVTable SUBTRACTION_VTABLE = { .calculate = subtraction };
const StrategyVTable MULTIPLICATION_VTABLE = { .calculate = multiplication };

// Функции для создания конкретных стратегий
AdditionStrategy* create_addition_strategy() {
    AdditionStrategy* strategy = (AdditionStrategy*)malloc(sizeof(AdditionStrategy));
    if (!strategy) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    strategy->vtable = &ADDITION_VTABLE;
    return (Strategy*)strategy;
}

SubtractionStrategy* create_subtraction_strategy() {
    SubtractionStrategy* strategy = (SubtractionStrategy*)malloc(sizeof(SubtractionStrategy));
    if (!strategy) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    strategy->vtable = &SUBTRACTION_VTABLE;
    return (Strategy*)strategy;
}

MultiplicationStrategy* create_multiplication_strategy() {
    MultiplicationStrategy* strategy = (MultiplicationStrategy*)malloc(sizeof(MultiplicationStrategy));
    if (!strategy) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    strategy->vtable = &MULTIPLICATION_VTABLE;
    return (Strategy*)strategy;
}

// Контекст, использующий стратегию
typedef struct Context {
    Strategy* strategy;
} Context;

Context* create_context(Strategy* strategy) {
    Context* context = (Context*)malloc(sizeof(Context));
    if (!context) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    context->strategy = strategy;
    return context;
}

void set_strategy(Context* context, Strategy* strategy) {
    return context->strategy = strategy;
}

double execute_strategy(Context* context, double a, double b) {
    return context->strategy->vtable->calculate(a, b);
}

void destroy_context(Context* context) {
    free(context);
}

void destroy_strategy(Strategy* strategy) {
    free(strategy);
}

int main() {
    Context* context = create_context(create_addition_strategy());
    
    double result = execute_strategy(context, 5, 7);
    printf("Результат сложения: %.2f\n", result);
    
    set_strategy(context, create_subtraction_strategy());
    result = execute_strategy(context, 15, 8);
    printf("Результат вычитания: %.2f\n", result);
    
    set_strategy(context, create_multiplication_strategy());
    result = execute_strategy(context, 6, 9);
    printf("Результат умножения: %.2f\n", result);
    
    destroy_strategy(context->strategy);
    destroy_context(context);
    
    return 0;
}

