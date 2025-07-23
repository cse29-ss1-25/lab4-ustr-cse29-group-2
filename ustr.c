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

}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this

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

