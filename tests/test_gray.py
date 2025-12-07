import numpy as np

from hw1_mlops import rgb_to_gray


def test_rgb_to_gray_random():
    height, width = 100, 100
    img = np.random.randint(0, 256, (height, width, 3), dtype=np.uint8)

    result = rgb_to_gray(img)

    r = img[:, :, 0].astype(np.float32)
    g = img[:, :, 1].astype(np.float32)
    b = img[:, :, 2].astype(np.float32)

    expected = 0.299 * r + 0.587 * g + 0.114 * b
    expected = expected.astype(np.uint8)

    assert result.shape == (height, width)

    diff = np.abs(result.astype(np.int16) - expected.astype(np.int16))

    assert np.max(diff) <= 1
    assert np.mean(diff == 0) > 0.99


def test_rgb_to_gray_known_values():
    img = np.zeros((1, 1, 3), dtype=np.uint8)
    assert rgb_to_gray(img)[0, 0] == 0

    img = np.full((1, 1, 3), 255, dtype=np.uint8)
    val = rgb_to_gray(img)[0, 0]
    assert abs(val - 255) <= 1

    img = np.array([[[255, 0, 0]]], dtype=np.uint8)
    expected = int(0.299 * 255)
    assert abs(rgb_to_gray(img)[0, 0] - expected) <= 1
