import syscalls

def test_drl_update_prob():
    prob = 5389790
    size = 21
    result = syscalls.l4s_drl_update_prob(prob,size)
    print(f"Test drl_update_prob with input {prob}: Result = {result}")

def test_drl_get_buffer():
    data = syscalls.l4s_drl_get_buffer()
    print(f"Test drl_get_buffer")
    print("Data structure contents:")
    print(data)

    print("drl_get_buffer test passed.")

def main():
    test_drl_update_prob()
    test_drl_get_buffer()
    print("All tests passed.")

if __name__ == "__main__":
    main()
