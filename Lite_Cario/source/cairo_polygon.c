﻿
#include <stdlib.h>
#include "cairoint.h"

#define CAIRO_POLYGON_GROWTH_INC 10

/* private functions */

static cairo_status_t
_cairo_polygon_grow_by (cairo_polygon_t *polygon, int additional);

void
_cairo_polygon_init (cairo_polygon_t *polygon)
{
    polygon->num_edges = 0;

    polygon->edges_size = 0;
    polygon->edges = NULL;

    polygon->has_current_point = 0;
}

void
_cairo_polygon_fini (cairo_polygon_t *polygon)
{
    if (polygon->edges_size) {
	free (polygon->edges);
	polygon->edges = NULL;
	polygon->edges_size = 0;
	polygon->num_edges = 0;
    }

    polygon->has_current_point = 0;
}

static cairo_status_t
_cairo_polygon_grow_by (cairo_polygon_t *polygon, int additional)
{
    cairo_edge_t *new_edges;
    int old_size = polygon->edges_size;
    int new_size = polygon->num_edges + additional;

    if (new_size <= polygon->edges_size) {
	return CAIRO_STATUS_SUCCESS;
    }

    polygon->edges_size = new_size;
    new_edges = realloc (polygon->edges, polygon->edges_size * sizeof (cairo_edge_t));

    if (new_edges == NULL) {
	polygon->edges_size = old_size;
	return CAIRO_STATUS_NO_MEMORY;
    }

    polygon->edges = new_edges;

    return CAIRO_STATUS_SUCCESS;
}

cairo_status_t
_cairo_polygon_add_edge (cairo_polygon_t *polygon, cairo_point_t *p1, cairo_point_t *p2)
{
    cairo_status_t status;
    cairo_edge_t *edge;

    /* drop horizontal edges */
    if (p1->y == p2->y) {
	goto DONE;
    }

    if (polygon->num_edges >= polygon->edges_size) {
	status = _cairo_polygon_grow_by (polygon, CAIRO_POLYGON_GROWTH_INC);
	if (status) {
	    return status;
	}
    }

    edge = &polygon->edges[polygon->num_edges];
    if (p1->y < p2->y) {
	edge->edge.p1 = *p1;
	edge->edge.p2 = *p2;
	edge->clockWise = 1;
    } else {
	edge->edge.p1 = *p2;
	edge->edge.p2 = *p1;
	edge->clockWise = 0;
    }

    polygon->num_edges++;

  DONE:
    _cairo_polygon_move_to (polygon, p2);

    return CAIRO_STATUS_SUCCESS;
}

cairo_status_t 
_cairo_polygon_move_to (cairo_polygon_t *polygon, cairo_point_t *point)
{
    if (! polygon->has_current_point)
	polygon->first_point = *point;
    polygon->current_point = *point;
    polygon->has_current_point = 1;

    return CAIRO_STATUS_SUCCESS;
}

cairo_status_t
_cairo_polygon_line_to (cairo_polygon_t *polygon, cairo_point_t *point)
{
    cairo_status_t status = CAIRO_STATUS_SUCCESS;

    if (polygon->has_current_point) {
	status = _cairo_polygon_add_edge (polygon, &polygon->current_point, point);
    } else {
	_cairo_polygon_move_to (polygon, point);
    }

    return status;
}

cairo_status_t
_cairo_polygon_close (cairo_polygon_t *polygon)
{
    cairo_status_t status;

    if (polygon->has_current_point) {
	status = _cairo_polygon_add_edge (polygon,
					  &polygon->current_point,
					  &polygon->first_point);
	if (status)
	    return status;

	polygon->has_current_point = 0;
    }

    return CAIRO_STATUS_SUCCESS;
}
