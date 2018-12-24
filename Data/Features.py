from keras.applications.vgg16 import VGG16
from keras.preprocessing import image
from keras.applications.vgg16 import preprocess_input
from keras.preprocessing.image import ImageDataGenerator
import numpy as np

model = VGG16(weights='imagenet', include_top=False)
train_datagen = ImageDataGenerator(rescale = 1./255, shear_range = 0.2, zoom_range = 0.2, horizontal_flip = True)
training_set = train_datagen.flow_from_directory('img', target_size = (100, 100), batch_size = 32, class_mode = 'binary')
locate = training_set.filenames
clas = training_set.classes
count = clas.shape[0]

features = np.zeros((count, 513))

for i in range(count):
    img_path = 'img/'+locate[i]
    img = image.load_img(img_path, target_size=(100, 100))
    x = image.img_to_array(img)
    x = np.expand_dims(x, axis=0)
    x = preprocess_input(x)
    feature = model.predict(x)
    features[i,0] = clas[i]
    features[i,1:] = feature[0,0,0,:]

import csv
with open("features.csv","w+") as my_csv:
    csvWriter = csv.writer(my_csv,delimiter=',')
    csvWriter.writerows(features)
