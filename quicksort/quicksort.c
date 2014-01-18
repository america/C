#define SWAP(a, b){int temp; temp = a; a = b; b = temp;}

void quick_sort_sub(int *data, int left, int right)
{
  int left_index = left;
  int right_index = right;
  int pivot = data[(left + right) / 2];

  while(left_index <= right_index){
    for(;data[left_index] < pivot; left_index++){
      ;
    }
    for(;data[right_index] > pivot; right_index--){
      ;
    }

    if(left_index <= right_index){
      SWAP(data[left_index], data[right_index]);
      left_index++;
      right_index--;
    }
  }

  if(right_index > left){
    quick_sort_sub(data, left, right_index);
  }
  if(left_index < right){
    quick_sort_sub(data, left_index, right);
  }
}

void quick_sort(int *data, int data_size)
{
  quick_sort_sub(data, 0, data_size - 1);
}
