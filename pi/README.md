# Setup

```
brew install portaudio
```

Then, install the python requirements:
```
pip3 install -r requirements.txt
```

The last release of [Adafruit-BluefruitLE](https://github.com/adafruit/Adafruit_Python_BluefruitLE) does not contain a patch necessary for this repo to run.
So, install it from source on the master branch.
In another directory, but using the same virtual env:

```
 git clone https://github.com/adafruit/Adafruit_Python_BluefruitLE

 cd Adafruit_Python_BluefruitLE

 python3 setup.py install
 ```

 # Running

 ```
 python3 dragon_ctl.py --name "Dragon Lamp"
 ```

