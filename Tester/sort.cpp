#include "catch.hpp"

extern "C"
{
	#include <liblogic.h>
}

#include <cstring>

using t_file_node_ptr = t_file_node*;

t_file_node_ptr create(const char* name);

TEST_CASE("Basic sort", "[sort]")
{
	const char* name1 = "1";
	const char* name2 = "2";
	const char* name3 = "3";
	const char* name4 = "4";
	const char* name5 = "5";
	const char* name6 = "6";
	const char* name9 = "9";
	t_file_node_ptr node3_1 = create(name3);
	t_file_node_ptr node1_1 = create(name1);
	t_file_node_ptr node4 = create(name4);
	t_file_node_ptr node1_2 = create(name1);
	t_file_node_ptr node5_1 = create(name5);
	t_file_node_ptr node9 = create(name9);
	t_file_node_ptr node2 = create(name2);
	t_file_node_ptr node6 = create(name6);
	t_file_node_ptr node5_2 = create(name5);
	t_file_node_ptr node3_2 = create(name3);
	node3_1->next = node1_1;
	node1_1->next = node4;
	node4->next = node1_2;
	node1_2->next = node5_1;
	node5_1->next = node9;
	node9->next = node2;
	node2->next = node6;
	node6->next = node5_2;
	node5_2->next = node3_2;
	node3_2->prev = node5_2;
	node5_2->prev = node6;
	node6->prev= node2;
	node2->prev = node9;
	node9->prev = node5_1;
	node5_1->prev = node1_2;
	node1_2->prev = node4;
	node4->prev = node1_1;
	node1_1->prev = node3_1;
	REQUIRE(strcmp(node3_1->info.name, name3) == 0);
	REQUIRE(strcmp(node3_1->next->info.name, name1) == 0);
	REQUIRE(strcmp(node3_1->next->next->info.name, name4) == 0);
	REQUIRE(strcmp(node3_1->next->next->next->info.name, name1) == 0);
	REQUIRE(strcmp(node3_1->next->next->next->next->info.name, name5) == 0);
	REQUIRE(strcmp(node3_1->next->next->next->next->next->info.name, name9) == 0);
	REQUIRE(strcmp(node3_1->next->next->next->next->next->next->info.name, name2) == 0);
	REQUIRE(strcmp(node3_1->next->next->next->next->next->next->next->info.name, name6) == 0);
	REQUIRE(strcmp(node3_1->next->next->next->next->next->next->next->next->info.name, name5) == 0);
	REQUIRE(strcmp(node3_1->next->next->next->next->next->next->next->next->next->info.name, name3) == 0);
	REQUIRE(!node3_1->next->next->next->next->next->next->next->next->next->next);
	REQUIRE(strcmp(node3_2->info.name, name3) == 0);
	REQUIRE(strcmp(node3_2->prev->info.name, name5) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->info.name, name6) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->prev->info.name, name2) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->prev->prev->info.name, name9) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->prev->prev->prev->info.name, name5) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->prev->prev->prev->prev->info.name, name1) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->prev->prev->prev->prev->prev->info.name, name4) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->prev->prev->prev->prev->prev->prev->info.name, name1) == 0);
	REQUIRE(strcmp(node3_2->prev->prev->prev->prev->prev->prev->prev->prev->prev->info.name, name3) == 0);
	REQUIRE(!node3_2->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev);
	{
		t_file_list list;
		list.head = node3_1;
		list.last = node3_2;
		sort_file_list(&list, [](const auto* a, const auto* b)
			{ return std::strcmp(a->info.name, b->info.name) < 0; });
		// Is    : 3 1 4 1 5 9 2 6 5 3
		// Should: 1 1 2 3 3 4 5 5 6 9
		REQUIRE(strcmp(list.head->info.name, name1) == 0);
		REQUIRE(strcmp(list.head->next->info.name, name1) == 0);
		REQUIRE(strcmp(list.head->next->next->info.name, name2) == 0);
		REQUIRE(strcmp(list.head->next->next->next->info.name, name3) == 0);
		REQUIRE(strcmp(list.head->next->next->next->next->info.name, name3) == 0);
		REQUIRE(strcmp(list.head->next->next->next->next->next->info.name, name4) == 0);
		REQUIRE(strcmp(list.head->next->next->next->next->next->next->info.name, name5) == 0);
		REQUIRE(strcmp(list.head->next->next->next->next->next->next->next->info.name, name5) == 0);
		REQUIRE(strcmp(list.head->next->next->next->next->next->next->next->next->info.name, name6) == 0);
		REQUIRE(strcmp(list.head->next->next->next->next->next->next->next->next->next->info.name, name9) == 0);
		REQUIRE(!list.head->next->next->next->next->next->next->next->next->next->next);
		REQUIRE(strcmp(list.last->info.name, name9) == 0);
		REQUIRE(strcmp(list.last->prev->info.name, name6) == 0);
		REQUIRE(strcmp(list.last->prev->prev->info.name, name5) == 0);
		REQUIRE(strcmp(list.last->prev->prev->prev->info.name, name5) == 0);
		REQUIRE(strcmp(list.last->prev->prev->prev->prev->info.name, name4) == 0);
		REQUIRE(strcmp(list.last->prev->prev->prev->prev->prev->info.name, name3) == 0);
		REQUIRE(strcmp(list.last->prev->prev->prev->prev->prev->prev->info.name, name3) == 0);
		REQUIRE(strcmp(list.last->prev->prev->prev->prev->prev->prev->prev->info.name, name2) == 0);
		REQUIRE(strcmp(list.last->prev->prev->prev->prev->prev->prev->prev->prev->info.name, name1) == 0);
		REQUIRE(strcmp(list.last->prev->prev->prev->prev->prev->prev->prev->prev->prev->info.name, name1) == 0);
		REQUIRE(!list.last->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev);
	}
	t_file_node_ptr it = node3_1;
	while (it)
	{
		t_file_node_ptr temp = it->next;
		delete it;
		it = temp;
	}
}
