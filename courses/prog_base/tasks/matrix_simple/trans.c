void printMatrix (int mat [4][4])
{
    int i, j;

    for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf ("%i\t", mat [i][j]);
		}
		printf ("\n");
	}
	printf ("\n");
}

void fillRand(int mat[4][4])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			mat[i][j] = rand()%1999-999;
		}

	}

}


void transposSide(int mat[4][4]);
{
	int i;
	int j;
	int a, b;
	int mat1 [4][4];

	for (i = 0, a = 3; i < 4; i++, a--)
	{
		for (j = 0, b = 3; j < 4; j++, b--)
		{
		    mat1 [i][j] = mat [b][a];

		}
	}

    for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{

            mat [i][j] = mat1[i][j];
		}
	}
}

void rotateCW180(int mat[4][4])
{
    int i,j;
    int matCW [4][4];
    int a,b;

    for (i = 0, a = 3 ; i < 4; i++, a--)
    {
        for (j = 0, b = 3; j < 4; j++, b--)
        {
            matCW[a][b] = mat [i][j];
        }
    }

    for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                mat [i][j] = matCW[i][j];
            }
        }
}


void flipH(int mat[4][4])
{
    int i, j, k;
    int mat3 [4][4];

    for (i = 0; i < 4; i++)
    {
        for (j = 3, k = 0; j >= 0; j--, k++)
        {
            mat3[i][k] = mat [i][j];
        }
    }


     for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            mat[i][j] = mat3[i][j];
        }
    }
}
