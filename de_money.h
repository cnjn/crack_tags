#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
        uint32_t original;
        uint8_t *data;
        size_t size;
} number_t;

number_t *number_init(uint32_t num)
{
        uint8_t buff[10];        // uint32_t 最大4294967295
        size_t index = 0;
        uint32_t original = num;
        while(num)
        {
                buff[index++] = num % 10;
                num /= 10;
        }

        number_t *number = (number_t *)malloc(sizeof(number_t));
        number->data = (uint8_t *)malloc((index + 1) / 2);
        number->size = 0;
        number->original = original;
        for(size_t i = 0; i < index;)
        {
                uint8_t temp = buff[i++];
                if(i < index)
                        temp |= (buff[i++]) << 4;
                number->data[number->size++] = temp;
        }

        return number;
}

void number_deinit(number_t *number)
{
        free(number->data);
        free(number);
}

void number_print(const number_t *number)
{
        printf("%u: ", number->original);
        for(size_t i = 0; i < number->size; ++i)
                printf("0x%x ", number->data[i]);
        if(number->original == 0)
                printf("0x%x", 0);
        printf("\n");
}

number_t *number_add(const number_t *a, const number_t *b)
{
        return number_init(a->original + b->original);
}

number_t *number_sub(const number_t *a, const number_t *b)
{
        return number_init(a->original - b->original);
}

number_t *number_mul(const number_t *a, const number_t *b)
{
        return number_init(a->original * b->original);
}

number_t *number_div(const number_t *a, const number_t *b)
{
        return number_init(a->original / b->original);
}
/*
int main(void)
{
        number_t *a = number_init(0);
        number_t *b = number_init(12);
        number_t *sum = number_add(a, b);
        number_t *sub = number_sub(a, b);
        number_t *mul = number_mul(a, b);
        number_t *div = number_div(a, b);
        printf("a -> "); number_print(a);
        printf("b -> "); number_print(b);
        printf("sum -> "); number_print(sum);
        printf("sub -> "); number_print(sub);
        printf("mul -> "); number_print(mul);
        printf("div -> "); number_print(div);
        number_deinit(a);
        number_deinit(b);
        number_deinit(sum);
        number_deinit(sub);
        number_deinit(mul);
        number_deinit(div);
        return 0;
}
*/