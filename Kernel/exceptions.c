#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE 6

static void zeroDivision() {
	// Handler para manejar excepcíon
}

static void invalidOpcode() {
    // Handler para manejar excepcíon
}

void exceptionDispatcher(int exception) {
    switch (exception) {
        case ZERO_EXCEPTION_ID:
            zeroDivision();
            break;
        case INVALID_OPCODE:
            invalidOpcode();
            break;
    }
}