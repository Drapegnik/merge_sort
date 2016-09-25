//
// Created by Ivan Pazhitnykh on 22.09.16.
//

int *merge(int *l_buff, int *r_buff, int l_size, int r_size) {
    int width = l_size + r_size;
    int *target = new int[width];

    int l_cur = 0, r_cur = 0;

    for (int i = 0; i < width; i++) {
        if (l_cur < l_size && r_cur < r_size)
            target[i] = (l_buff[l_cur] < r_buff[r_cur]) ? l_buff[l_cur++] : r_buff[r_cur++];
        else if (l_cur < l_size)
            target[i] = l_buff[l_cur++];
        else
            target[i] = r_buff[r_cur++];
    }

    return target;
}

int *merge_sort(int *data, int left, int right) {
    if (left == right) {
        int *temp = new int[1];
        temp[0] = data[left];
        return temp;
    }

    int middle = (left + right) / 2;

    int *l_buff = merge_sort(data, left, middle);
    int *r_buff = merge_sort(data, middle + 1, right);

    return merge(l_buff, r_buff, middle - left + 1, right - middle);
}