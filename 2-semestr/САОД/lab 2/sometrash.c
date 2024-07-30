printf("Эксперимент 1 lookup ");
    printf("\n");

    struct listnode *hashtab[N];
    hashtab_init(hashtab);
    
    struct bstree *tree = bstree_create(words[0], 0);

    for (int i = 2, m = 0; i <= 200000; i++)
    {

        bstree_add(tree, words[i - 1], i - 1);
        hashtab_add(hashtab, words[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            m += 1;
            // hast_table |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
            char *w2 = words[getrand(0, i - 1)];

            long double timer2 = wtime();
            for(int i=0;i<N-1;i++){
            struct listnode *node2 = hashtab_lookup(hashtab, w2);
            }
            
            timer2 = wtime() - timer2;

            // trie |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
            char *w = words[getrand(0, i - 1)];

            double timer1 = wtime();
            struct bstree *node = bstree_lookup(tree, w);
            timer1 = wtime() - timer1;

            // print |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

            printf("\n%.2d   n = %d; trie_lkup_time = %.9f hash_lkup_time = %.9Lf", m, i, timer1, timer2);
            FILE *file = fopen("lookup.dat", "a");
            fprintf(file, "%.2d %d %.15f %.15f\n", m, i, timer1, timer2);
            fclose(file);
        }
    }
// эксперимент 2 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
printf("\n");
printf("Эксперимент 2 add ");
printf("\n");
bstree *tree2 = bstree_create(words[0], 0);
hashtab_init(hashtab);

for (int i = 10000, m = 0; i <= 200000; i += 10000)
{
    double timer1 = wtime();
    for (int j = 0; j < i; j++)
    {
        bstree_add(tree2, words[j], j);
    }
    timer1 = wtime() - timer1;

    double timer2 = wtime();
    for (int j = 0; j < i; j++)
    {
        hashtab_add(hashtab, words[j], j);
        hashtab_delete(hashtab, words[j]);
    }
    timer2 = wtime() - timer2;
    m += 1;
    printf("\n%.2d   n = %d; trie_add_time = %.9f hash_add_time = %.9f", m, i, timer1, timer2);
}
printf("\n");

// эксперимент 6 KP ELF  0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\

printf("\n");
printf("Эксперимент 6 KP ELF ");
printf("\n");

struct listnode *hashtab_KP[N];
struct listnode *hashtab_ELF[N];

int collisions_KP = 0;
int collisions_ELF = 0;

hashtab_init(hashtab_KP);
hashtab_init(hashtab_ELF);
for (int i = 2, m = 0; i <= 200000; i++)
{

    hashtab_add(hashtab_KP, words[i - 1], i - 1, &collisions_KP);

    hashtab_add_ELF(hashtab_ELF, words[i - 1], i - 1, &collisions_ELF);

    struct listnode *node = hashtab_KP[i];

    node = hashtab_ELF[i];
    if (i % 10000 == 0)
    {
        m += 1;

        // KP
        char *w2 = words[getrand(0, i - 1)];
        double timer2 = wtime();
        struct listnode *node2 = hashtab_lookup(hashtab_KP, w2);
        timer2 = wtime() - timer2;

        // ELF
        char *w3 = words[getrand(0, i - 1)];
        double timer1 = wtime();
        struct listnode *node3 = hashtab_lookup_ELF(hashtab_ELF, w2);
        timer1 = wtime() - timer1;

        // collis

        while (node)
        {
            if (node->next)
            {
                collisions_KP++;
            }
            node = node->next;
        }

        while (node)
        {
            if (node->next)
            {
                collisions_ELF++;
            }
            node = node->next;
        }

        // print

        printf("\n%.2d   n = %d; hashKP_lkup_time = %.9f hashELF_lkup_time = %.9f hashKP_collis = %d hashELF_collis = %d", m, i, timer2, timer1, collisions_KP, collisions_ELF);
        FILE *file = fopen("lookup.dat", "a");
        fprintf(file, "%d %.15f %.15f\n", i, timer1, timer2);
        fclose(file);
    }
}
printf("\n");



for (int i = 1000, m = 0; i <= 200000; i += 10000)
    {
        bstree_add(tree2, words[i - 1], i - 1);
        hashtab_add(hashtab2, words[i - 1], i - 1);
        if (i % 10000 == 0)
        {   m += 1;

            double timer1 = wtime();
            bstree_add(tree2, words[i - 1], i - 1);
            timer1 = wtime() - timer1;
            
            
            double timer2 = wtime();
            hashtab_add(hashtab2, words[i - 1], i - 1);
            timer2 = wtime() - timer2;

            
            printf("\n%.2d   n = %d; trie_add_time = %.6f hash_add_time = %.6f", m, i, timer1, timer2);
        
        FILE *file2 = fopen("add.dat", "w");
        fprintf(file2, "%d %.6f %.6f\n",i, timer1, timer2);
        fclose(file2);
        }

    }


    //trie
        struct bstree *tree2 = bstree_create(words[0], 0);
        for (int j = 0; j < i; j++)
        {
            bstree_add(tree2, words[j], j);
        }

        double timer1 = wtime();
        bstree_add(tree2, words[i], i);
        timer1 = wtime() - timer1;

        
         // trie 

            char *w = words[getrand(0, i - 1)];

            double timer1 = wtime();
            
            
            struct bstree *node1 = bstree_lookup(tree1, w);
            timer1 = wtime() - timer1;


            // hast_table 

            char *w2 = words[getrand(0, i - 1)];

            double timer2 = wtime();
             //for(int i=0;i<N-1;i++){}
                struct listnode *node2 = hashtab_lookup(hashtab1, w2);
            
            timer2 = wtime() - timer2;


            struct listnode *hashtab1[size];

    hashtab_init(hashtab1);
    
    struct bstree *tree1 = bstree_create(words[0], 0);

    for (int i = 2, m = 0; i <= 200000; i++)
    {

        bstree_add(tree1, words[i - 1], i - 1);

        hashtab_add(hashtab1, words[i - 1], i - 1);
        
    }
    for (int i = 10000, m = 0; i <= 200000; i+=10000)
    {
         m += 1;

        double total_time_trie = 0;

        for (int j = 1; j <= i; j++)
        {
            double start_time = wtime();
            char *w = words[getrand(0, i - 1)];
            struct bstree *node1 = bstree_lookup(tree1, w);
            double end_time = wtime();
            total_time_trie += (end_time - start_time);
        }

            double timer1 = total_time_trie / i;
           
        double total_time_hash = 0;

        for (int j = 1; j <= i; j++)
        {
            double start_time = wtime();
            char *w = words[getrand(0, i - 1)];
            struct bstree *node1 = bstree_lookup(tree1, w);
            double end_time = wtime();
            total_time_hash += (end_time - start_time);
        }

            double timer2 = total_time_hash / i;
            

            // print 

            printf("\n%.2d   n = %d; trie_lkup_time = %.9f hash_lkup_time = %.9f", m, i, timer1, timer2);
            FILE *file1 = fopen("lookup.dat", "w");
            fprintf(file1, "%d %.8f %.8f\n",i, timer1, timer2);
            fclose(file1);
    }