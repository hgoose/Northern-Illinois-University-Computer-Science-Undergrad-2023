
double discount(double amount) {

    if (amount >= 100.0f) {
        return amount - (amount * 0.15f);

    } else if (amount < 100.0f && amount >= 50.0f) {
        return amount - (amount * 0.1f);

    } else {
        return amount - (amount * 0.05f);
    }

}

