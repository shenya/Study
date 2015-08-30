/*This is bubble sort*/
void bubble_sort(int a[], int size)
{
    int i, j;
    int temp;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i -1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

/* This is insert sort */
void insert_sort(int a[], int size)
{
    int i, j;
    int temp;

    for (i = 1; i < size; i++) {
        temp = a[i];
        for(j = i - 1; j >= 0; j--) {
            if (a[j] > temp) {
                a[j + 1] = a[j];
            } else {
               break;
            }
        }
        a[j + 1] = temp;
    }
}

/* This is selection sort */
void select_sort(int a[], int size)
{
    int i, j;
    int index;
    int temp;

    for (i = 0; i < size -1; i++) {
        index = i;
        for(j = i + 1; j < size; j++) {
            if (a[j] < a[index]) {
                index = j;
            }
        }
        if (index != i) {
            temp = a[i];
            a[i] = a[index];
            a[index] = temp;
        }
    }
}

/* This is shell sort */
void shell_sort(int a[], int size)
{
    int i, j, k;
    int temp;

    k = size/2;

    while(k >= 1) {
        for (i = k; i < size; i++) {
            temp = a[i];
            j = i - k;
            while (j >= 0 && a[j] > temp) {
                a[j + k] = a[j];
                j = j - k;
            }
            a[j + k] = temp;
        }

        k = k/2;
    }
}

/* This is quick sort */
void quick_sort(int a[], int left, int right)
{
    int i, j, key;
    i = left;
    j = right;

    key = a[i];

    if (left >= right)
        return;

    while (i < j) {

        while (j > i && a[j] >= key)
            j--;
        a[i] = a[j];

        while (i < j && a[i] <= key)
            i++;
        a[j] = a[i];
    }

    a[i] = key;
    quick_sort(a, left, i - 1);
    quick_sort(a, i + 1, right);
}
