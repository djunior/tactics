#ifndef __T_ERROR_H__
#define __T_ERROR_H__

enum T_ERROR{
	T_SUCCESS,
	T_ERROR_OUT_OF_BOUNDS,
	T_ERROR_OUT_OF_RANGE,
	T_ERROR_INVALID_LOCATION,
	T_ERROR_INVALID_UNIT,
	T_ERROR_INVALID_TARGET,
	T_ERROR_MAP_FULL,
	T_ERROR_UNIT_OUT_OF_MOVES,
	T_ERROR_UNIT_OUT_OF_ACTIONS,
	T_ERROR_UNKNOWN,
};

typedef enum T_ERROR T_ERROR;


#endif
