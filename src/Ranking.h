#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include "TextureManager.h"
#include "Input.h"
#include "Writer.h"
#include "Graphics.h"

#define MAX_RANK 10


class CRanking {

	public:

		CRanking();
		~CRanking();
		void init();
		bool CheckScore(int s);
		void SetScore(std::string n, int s);
		void SaveScores();
		void ResetRanking();
		void update(float time);
		void draw();

	private:

		int imatge_rank;

		CInput*				input;
		CTextureManager*	texman;
		CWriter*			escriptor;
	
};
