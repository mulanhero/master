import tensorflow as tf
import numpy as np

x = np.random.randint(100, size = 10)
print(x)
y = tf.Variable(x+5)
#x = tf.constant([35, 40, 45], name='x')
#y = tf.Variable(x + 5, name='y')

model = tf.global_variables_initializer()

with tf.Session() as session:
	session.run(model)
	print(session.run(y))
