# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>

#   define STREAM_ARRAY_SIZE	6000000

#   define NTIMES	100

#   define OFFSET	0

# define HLINE "-------------------------------------------------------------\n"


# define MIN(x,y) ((x)<(y)?(x):(y))
# define MAX(x,y) ((x)>(y)?(x):(y))


#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif

static STREAM_TYPE	a[STREAM_ARRAY_SIZE+OFFSET],
			b[STREAM_ARRAY_SIZE+OFFSET],
			c[STREAM_ARRAY_SIZE+OFFSET];

static double	avgtime = 0, maxtime = 0,
		mintime = FLT_MAX;


static double	bytes =  2 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE ; 

extern double mysecond();
extern void STREAM_load();
extern int omp_get_num_threads();

static void escape(void *p){
    asm volatile("" : : "g"(p) : "memory");
}


static void clobber(){
    asm volatile("" : : : "memory");
}

int main()
    {
    int			quantum, checktick();
    int			BytesPerWord;
    int			k;
    ssize_t		j;
    double		t, times[NTIMES];

    /* --- SETUP --- determine precision and check timing --- */

    BytesPerWord = sizeof(STREAM_TYPE);
    printf("This system uses %d bytes per array element.\n",
	BytesPerWord);

    printf(HLINE);
    printf("Array size = %llu (elements), Offset = %d (elements)\n" , (unsigned long long) STREAM_ARRAY_SIZE, OFFSET);
    printf("Memory per array = %.1f MiB (= %.1f GiB).\n", 
	BytesPerWord * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.0),
	BytesPerWord * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.0/1024.0));
    printf("Total memory required = %.1f MiB (= %.1f GiB).\n",
	(3.0 * BytesPerWord) * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.),
	(3.0 * BytesPerWord) * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024./1024.));
    printf("Each kernel will be executed %d times.\n", NTIMES);
    printf(" The *best* time for each kernel (excluding the first iteration)\n"); 
    printf(" will be used to compute the reported bandwidth.\n");

    printf(HLINE);
#pragma omp parallel 
    {
#pragma omp master
	{
	    k = omp_get_num_threads();
	    printf ("Number of Threads requested = %i\n",k);
        }
    }

#ifdef _OPENMP
	k = 0;
#pragma omp parallel
#pragma omp atomic 
		k++;
    printf ("Number of Threads counted = %i\n",k);
#endif

    /* Get initial value for system clock. */
#pragma omp parallel for
    for (j=0; j<STREAM_ARRAY_SIZE; j++) {
	    a[j] = rand()/10000.0;
	    b[j] = 2.0;
	    c[j] = rand()/10000.0;
	}

    printf(HLINE);

    quantum = checktick();
    t = mysecond();
#pragma omp parallel for
    for (j = 0; j < STREAM_ARRAY_SIZE; j++)
		a[j] = 2.0E0 * a[j];
    t = 1.0E6 * (mysecond() - t);


    
    /*	--- MAIN LOOP --- repeat test cases NTIMES times --- */
    for (k=0; k<NTIMES; k++)
	{
    escape(&c);
    escape(&a); 
	times[k] = mysecond();
        STREAM_load();
	times[k] = mysecond() - times[k];
    clobber(c);
    clobber(a);
	}

    /*	--- SUMMARY --- */

    for (k=1; k<NTIMES; k++) /* note -- skip first iteration */
	{
	    avgtime = avgtime + times[k];
	    mintime = MIN(mintime, times[k]);
	    maxtime = MAX(maxtime, times[k]);

	}
    
    printf("Best Rate MB/s Avg Rate MB/s  Avg time     Min time     Max time\n");
		avgtime = avgtime/(double)(NTIMES-1);

		printf("%12.1f %12.1f  %11.6f  %11.6f  %11.6f\n\n\n",
           1.0E-06 * bytes/mintime,
	       1.0E-06 * bytes/avgtime,
	       avgtime,
	       mintime,
	       maxtime);


    return 0;
}

# define	M	20

int
checktick()
    {
    int		i, minDelta, Delta;
    double	t1, t2, timesfound[M];

/*  Collect a sequence of M unique time values from the system. */

    for (i = 0; i < M; i++) {
	t1 = mysecond();
	while( ((t2=mysecond()) - t1) < 1.0E-6 )
	    ;
	timesfound[i] = t1 = t2;
	}

/*
 * Determine the minimum difference between these M values.
 * This result will be our estimate (in microseconds) for the
 * clock granularity.
 */

    minDelta = 1000000;
    for (i = 1; i < M; i++) {
	Delta = (int)( 1.0E6 * (timesfound[i]-timesfound[i-1]));
	minDelta = MIN(minDelta, MAX(Delta,0));
	}

   return(minDelta);
    }



/* A gettimeofday routine to give access to the wall
   clock timer on most UNIX-like systems.  */


double mysecond()
{
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

#ifndef abs
#define abs(a) ((a) >= 0 ? (a) : -(a))
#endif


void STREAM_load()
{
	ssize_t j;
	STREAM_TYPE temp;
#pragma omp parallel for
        for (j=0; j<STREAM_ARRAY_SIZE; j++)
            c[j] = a[j];
	    // temp = c[j];
}


