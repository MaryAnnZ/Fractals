#pragma once

static int  i = 0;

inline int generateUuid(){
	return i++;
}