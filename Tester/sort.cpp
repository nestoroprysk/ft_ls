#include "catch.hpp"

extern "C"
{
	#include <liblogic.h>
}

using t_file_node_ptr = t_file_node*;

t_file_node* create_node(const char* name, t_file_node* prev, t_file_node* next);
bool asBefore(t_file_node_ptr a, t_file_node_ptr b, t_file_node_ptr c,
	t_file_node_ptr d, t_file_node_ptr e);

const char* a_name = "1";
const char* b_name = "2";
const char* c_name = "3";
const char* d_name = "4";
const char* e_name = "5";

TEST_CASE("Swap nodes", "[sort]")
{
	t_file_node_ptr a, b, c, d, e;
	a = create_node(a_name, NULL, NULL);
	b = create_node(b_name, a, NULL);
	c = create_node(c_name, b, NULL);
	d = create_node(d_name, c, NULL);
	e = create_node(e_name, d, NULL);
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	{
		// 1 (2) 3 (4) 5
		// 1 (4) 3 (2) 5
		// Assymetry test 1
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&b, &d);
		REQUIRE(!asBefore(a, b, c, d, e));
		swap_nodes(&b, &d);
		REQUIRE(asBefore(a, b, c, d, e));
		// 1 2 (3) 4 5
		// 1 2 (3) 4 5
		// Assymetry test 2
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&c, &c);
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&c, &c);
		REQUIRE(asBefore(a, b, c, d, e));
		// 1 2 (3) (4) 5
		// 1 2 (4) (3) 5
		// Assymetry test 3
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&c, &d);
		REQUIRE(!asBefore(a, b, c, d, e));
		swap_nodes(&c, &d);
		REQUIRE(asBefore(a, b, c, d, e));
		// (1) 2 3 4 (5)
		// (5) 2 3 4 (1)
		// Assymetry test 4
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&a, &e);
		REQUIRE(!asBefore(a, b, c, d, e));
		swap_nodes(&e, &a);
		REQUIRE(asBefore(a, b, c, d, e));
	}
	{
		// 1 (2) 3 (4) 5
		// 1 (4) 3 (2) 5
		// basic test
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&b, &d);
		REQUIRE(strcmp(a->info.name, a_name) == 0);
		REQUIRE(strcmp(a->next->info.name, d_name) == 0);
		REQUIRE(strcmp(a->next->next->info.name, c_name) == 0);
		REQUIRE(strcmp(a->next->next->next->info.name, b_name) == 0);
		REQUIRE(strcmp(a->next->next->next->next->info.name, e_name) == 0);
		REQUIRE(strcmp(e->info.name, e_name) == 0);
		REQUIRE(strcmp(e->prev->info.name, b_name) == 0);
		REQUIRE(strcmp(e->prev->prev->info.name, c_name) == 0);
		REQUIRE(strcmp(e->prev->prev->prev->info.name, d_name) == 0);
		REQUIRE(strcmp(e->prev->prev->prev->prev->info.name, a_name) == 0);
		swap_nodes(&b, &d);
		REQUIRE(asBefore(a, b, c, d, e));
	}
	{
		// (1) 2 3 4 (5)
		// (5) 2 3 4 (1)
		// edge test
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&a, &e);
		REQUIRE(strcmp(a->info.name, e_name) == 0);
		REQUIRE(strcmp(a->next->info.name, b_name) == 0);
		REQUIRE(strcmp(a->next->next->info.name, c_name) == 0);
		REQUIRE(strcmp(a->next->next->next->info.name, d_name) == 0);
		REQUIRE(strcmp(a->next->next->next->next->info.name, a_name) == 0);
		REQUIRE(strcmp(e->info.name, a_name) == 0);
		REQUIRE(strcmp(e->prev->info.name, d_name) == 0);
		REQUIRE(strcmp(e->prev->prev->info.name, c_name) == 0);
		REQUIRE(strcmp(e->prev->prev->prev->info.name, b_name) == 0);
		REQUIRE(strcmp(e->prev->prev->prev->prev->info.name, e_name) == 0);
		swap_nodes(&a, &e);
		REQUIRE(asBefore(a, b, c, d, e));
	}
	{
		// (1) (2) 3 4 5
		// (2) (1) 3 4 5
		// neighbour test
		REQUIRE(asBefore(a, b, c, d, e));
		swap_nodes(&a, &b);
		REQUIRE(strcmp(a->info.name, b_name) == 0);
		REQUIRE(strcmp(a->next->info.name, a_name) == 0);
		REQUIRE(strcmp(a->next->next->info.name, c_name) == 0);
		REQUIRE(strcmp(a->next->next->next->info.name, d_name) == 0);
		REQUIRE(strcmp(a->next->next->next->next->info.name, e_name) == 0);
		REQUIRE(strcmp(e->info.name, e_name) == 0);
		REQUIRE(strcmp(e->prev->info.name, d_name) == 0);
		REQUIRE(strcmp(e->prev->prev->info.name, c_name) == 0);
		REQUIRE(strcmp(e->prev->prev->prev->info.name, a_name) == 0);
		REQUIRE(strcmp(e->prev->prev->prev->prev->info.name, b_name) == 0);
		swap_nodes(&a, &b);
		REQUIRE(asBefore(a, b, c, d, e));
	}
	delete a;
	delete b;
	delete c;
	delete d;
	delete e;
}

t_file_node* create_node(const char* name, t_file_node* prev, t_file_node* next)
{
	t_file_node* result = new t_file_node;
	strcpy(result->info.name, name);
	result->prev = prev;
	result->next= next;
	return result;
}

bool asBefore(t_file_node_ptr a, t_file_node_ptr b, t_file_node_ptr c,
	t_file_node_ptr d, t_file_node_ptr e)
{
	const size_t nbRequirments = 15;
	size_t i = 0;
	if (a->next == b) ++i;
	if (b->next == c) ++i;
	if (c->next == d) ++i;
	if (d->next == e) ++i;
	if (e->next == NULL) ++i;
	if (a->prev == NULL) ++i;
	if (b->prev == a) ++i;
	if (c->prev == b) ++i;
	if (d->prev == c) ++i;
	if (e->prev == d) ++i;
	if (strcmp(a->info.name, a_name) == 0) ++i;
	if (strcmp(b->info.name, b_name) == 0) ++i;
	if (strcmp(c->info.name, c_name) == 0) ++i;
	if (strcmp(d->info.name, d_name) == 0) ++i;
	if (strcmp(e->info.name, e_name) == 0) ++i;
	return i == nbRequirments;
}
