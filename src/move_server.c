#include <stdlib.h>
#include "move_server.h"

struct moves_t* moves_add(struct moves_t* moves, struct move_t move)
{
    moves->t = realloc(moves->t, (moves->current + 2) * sizeof(struct move_t));
    moves->current++;
    moves->t[moves->current] = move;
    return moves;
}

int is_move_valid(struct graph_t* graph, struct world_t* world,
	       struct moves_t* moves, struct move_t new_move)
{
    if (new_move.queen_src == new_move.queen_dst || new_move.arrow_dst == new_move.queen_dst ||
	new_move.queen_src > world->width * world->width ||
	new_move.queen_dst > world->width * world->width ||
	new_move.arrow_dst > world->width * world->width)
	//  TO DO || dst are not reachable (not straight line or something between)
	return 0;
    
    moves = moves_add(moves, new_move);
    world->idx[new_move.queen_dst] = world->idx[new_move.queen_src];
    world->idx[new_move.queen_src] = NO_SORT;
    world->idx[new_move.arrow_dst] = BLOCK;
    return 1;
}

void dirs_possible(enum dir_t* dirs, unsigned int src, unsigned int dst) {
    if (src > dst) {
	for (int i = 0; i < 2; i++) {
	    dirs[i] = i + 1;
	    dirs[i + 2] = i + 7;
	}
    }
    else {
	for (int i = 0; i < 4; i++) {
	    dirs[i] = i + 3;
	}
    }
}

int exists_neighbor(struct graph_t* graph, enum dir_t dir, unsigned int current) {
    enum dir_t new_dir;
    unsigned int idx;
    for (int k = graph->t->p[current]; k < graph->t->p[current+1]; k++) {
	idx = graph->t->i[k];
	new_dir = gsl_spmatrix_uint_get(graph->t, current, idx);
	if (new_dir == dir) {
	    return idx;
	}
    }
    return -1;
}

void print_moves(struct moves_t* moves)
{
    printf("[ ");
    for (unsigned int i = 0; i <= moves->current; i++) {
	printf("{ %d %d %d }  ", moves->t[i].queen_src, moves->t[i].queen_dst, moves->t[i].arrow_dst);
    }
    printf("]\n");
}

void free_moves(struct moves_t* moves)
{
    free(moves->t);
    free(moves);
}
