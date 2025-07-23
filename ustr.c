#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this
	if (start < 0 || end < 0 || start >= end || start >= s.codepoints || end > s.codepoints) {
		return new_ustr("");
	}

	int32_t byte_start = utf8_byte_offset(s.contents, start);
    	int32_t byte_end = utf8_byte_offset(s.contents, end);
    	int32_t sub_bytes = byte_end - byte_start;

	char* sub = malloc(sub_bytes + 1);
   	if (!sub) {
		 fprintf(stderr, "memory allocation failed in substring\n");
		 exit(1);
	}

	memcpy(sub, s.contents + byte_start, sub_bytes);
    	sub[sub_bytes] = '\0';
	UStr result = new_ustr(sub);
    	free(sub); 
	return results;
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this
	int32_t total_bytes = s1.bytes + s2.bytes;
	char* combined = malloc(total_bytes +1);
    	if (!combined) {
		fprintf(stderr, "Memory allocation failed in concat\n");
        	exit(1);
	}

	memcpy(combined, s1.contents, s1.bytes);
	memcpy(combined + s1.bytes, s2.contents, s2.bytes);
	combined[total_bytes] = '\0';

    	UStr result = new_ustr(combined);
    	free(combined);
    	return result;

}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this
	if (index < 0 || index >= s.codepoints) {
		return new_ustr(s.contents);
	}

	int32_t byte_a = utf8_byte_offset(s.contents, index);
    	int32_t byte_b = utf8_byte_offset(s.contents, index + 1);
    	int32_t new_len = s.bytes - (byte_b - byte_a);

	char* result = malloc(new_len + 1);
    	if (!result) {
		fprintf(stderr, "Memory allocation failed in removeAt\n");
        	exit(1);
	}

	memcpy(result, s.contents, byte_a);
	memcpy(result + byte_a, s.contents + byte_b, s.bytes - byte_b);
	result[new_len] = '\0';

    	UStr u = new_ustr(result);
    	free(result);
    	return u;
}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this
	char* reversed = malloc(s.bytes + 1);
	if (!reversed) {
		fprintf(stderr, "Memory allocation failed in reverse\n");
        	exit(1);
	}

	int32_t start_positions[s.codepoints];
    	int32_t cursor = 0;
    	for (int i = 0; i < s.codepoints; i++) {
		start_positions[i] = cursor;
        	cursor = cursor +utf8_codepoint_length(s.contents + cursor);
	}

	int32_t write_pos = 0;
    	for (int i = s.codepoints - 1; i >= 0; i--) {
		int32_t byte_start = start_positions[i];
        	int32_t cp_len = utf8_codepoint_length(s.contents + byte_start);
        	memcpy(reversed + write_pos, s.contents + byte_start, cp_len);
        	write_pos = write_pos + cp_len;
	}

	reversed[write_pos] = '\0';
    	UStr u = new_ustr(reversed);
    	free(reversed);
    	return u;
}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

