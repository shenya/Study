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

