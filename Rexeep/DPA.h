#pragma once

template <int sc>
struct PDA {
	std::string Name;
	PD_State States[sc];
	PD_State CurrentState;
	Stack<char> SymbolStack;
};

template <typename T>
struct Stack {
	T* _tape;
	int _index;

public:
	void Push(T item) {
		_tape[_index] = item;
		_index++;
	}

	void Pop() {
		_index--;
	}

	T Peek() {
		return _tape[_index];
	}
};


typedef struct 
{
	SymbolTranstionMap Transitions[10];
} PD_State;

typedef struct 
{
	PD_State NewState;
	const char* Top;
} PD_TransitionResult;


typedef bool (*SymbolEqualTo)(char input);

struct SymbolTranstionMap {
	std::string Symbol;
	SymbolEqualTo Equalizer;
};


struct IsEqual
{
public:
	bool ToWord(char in) {
		int code = (int)in;
		if (code > 96 && code < 123)
			return true;

		return false;
	}
};