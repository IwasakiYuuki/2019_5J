import math

HS0 = 1/math.sqrt(2)
HS1 = 1/math.sqrt(2)
HW0 = 1/math.sqrt(2)
HW1 = -1/math.sqrt(2)


def wavelet(input):
    scal = []
    wave = []
    for i in range(int(input.__len__()/2)):
        scal.append(HS0 * input[i*2] + HS1 * input[i*2+1])
        wave.append(HW0 * input[i*2] + HW1 * input[i*2+1])
    print('scaling=', scal)
    print('wavelet=', wave)
    if scal.__len__() == 1:
        return scal, wave
    else:
        return wavelet(scal)


if __name__ == '__main__':
    scal, wave = wavelet([10, 6, 2, 4, 8, 2, 6, 4])
