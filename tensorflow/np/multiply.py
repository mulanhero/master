import numpy as np

# 2-D array: 2 x 3
two_dim_matrix_one = np.array([[1, 2, 3], [4, 5, 6]])
another_two_dim_matrix_one = np.array([[7, 8, 9], [4, 7, 1]])

#element-wise product
element_wise = two_dim_matrix_one * another_two_dim_matrix_one
print('element wise product: %s' %(element_wise))

#element-wise product
element_wise_2 = np.multiply(two_dim_matrix_one, another_two_dim_matrix_one)
print('element wise product: %s' % (element_wise_2))
