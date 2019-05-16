import speech_recognition as sr

def create_recognizer():
    r = sr.Recognizer()
    r.energy_threshold = 300
    return r

def listen_and_recognize(r):
    with sr.Microphone(sample_rate=44100) as source:
        print("Listening...")
        audio = r.listen(source, None, 4)
        data = ""
        try:
            print("processing...")
            data = r.recognize_google(audio)
            print("Google Speech Recognition ", data)
        except sr.UnknownValueError:
            print("Google Speech Recognition could not understand your audio")
        except sr.RequestError as e:
            print("Could not request results from Google Speech Recognition service: {0}".format(e))
        return data

if __name__ == "__main__":
    r = create_recognizer()
    while True:
        listen_and_recognize(r)