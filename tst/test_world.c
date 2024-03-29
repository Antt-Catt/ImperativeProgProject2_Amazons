#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_world.h"

void world_init__test()
{
    printf("\t%s", __func__);

    struct world_t* world = world_init(5);

    assert(world->width == 5);

    for (int i = 0; i < 5 * 5; i++) {
        assert(world->idx[i] == NO_SORT);
    }

    free_world(world);

    printf("\t\tOK\n");
}

void world_set__test()
{
    printf("\t%s", __func__);

    struct world_t* world = world_init(5);

    world_set(world, 8, B_QUEEN);
    world_set(world, 15, W_QUEEN);
    world_set(world, 21, BLOCK);
    assert(world->idx[8] == B_QUEEN);
    assert(world->idx[15] == W_QUEEN);
    assert(world->idx[21] == BLOCK);

    free_world(world);

    printf("\t\t\tOK\n");
}

void world_get__test()
{
    printf("\t%s", __func__);

    struct world_t* world = world_init(5);

    world_set(world, 8, B_QUEEN);
    world_set(world, 15, W_QUEEN);
    world_set(world, 21, BLOCK);
    assert(world_get(world, 8) == B_QUEEN);
    assert(world_get(world, 15) == W_QUEEN);
    assert(world_get(world, 21) == BLOCK);

    free_world(world);

    printf("\t\t\tOK\n");
}

void compute_queens_pos__test()
{
    printf("\t%s", __func__);

    struct world_t* world = world_init(5);

    unsigned int* queens[2];
    queens[0] = malloc(sizeof(unsigned int) * 4);
    queens[1] = malloc(sizeof(unsigned int) * 4);
    compute_queens_pos(5, world, 4, queens);

    assert(world_get(world, 1) == B_QUEEN);
    assert(world_get(world, 3) == B_QUEEN);
    assert(world_get(world, 5) == B_QUEEN);
    assert(world_get(world, 9) == B_QUEEN);
    assert(world_get(world, 23) == W_QUEEN);
    assert(world_get(world, 21) == W_QUEEN);
    assert(world_get(world, 19) == W_QUEEN);
    assert(world_get(world, 15) == W_QUEEN);

    assert(queens[0][0] == 1);
    assert(queens[0][1] == 3);
    assert(queens[0][2] == 5);
    assert(queens[0][3] == 9);
    assert(queens[1][0] == 21);
    assert(queens[1][1] == 15);
    assert(queens[1][2] == 19);
    assert(queens[1][3] == 23);

    free_world(world);
    free_queens(queens);

    printf("\tOK\n");
}
