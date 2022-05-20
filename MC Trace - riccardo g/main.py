import numpy as np
import matplotlib.pyplot as plt

"""
Genera una matrice  300x300 B con Bij campionato uniformemente nell'intervallo [0,1]. La matrice A = BTB è 
semidefinita positiva. Calcola ||A||2F e Tr(A) dalle definizioni. Usa MonteCarloTrace per stimare 100 volte Tr(A) 
con M=5,10,25 e 100. Costruisci un istogramma con le stime ottenute e commenta il significato delle posizioni 
nell'istogramma occupate da Tr(A) e Tr(A) ± σM (usando per σM uno dei 100 valori calcolati per ogni M). 
Confronta σ2M con 2 ||A||2F/M. 
"""

def MonteCarloTrace(matrix, M):
    X = [0]

    for m in range(1, M + 1):
        # Rademacher
        u = []
        for uu in range(0, len(matrix)):
            if np.random.randint(0, 2) == 0:
                u.append(-1)
            else:
                u.append(1)
        u = np.array(u)

        # oracolo
        X_m = (u.transpose()) @ matrix @ u

        X.append(X[m - 1] + (X_m - X[m - 1]) / m)

    sigma_squared = 0
    for m in range(1, M + 1):
        sigma_squared += (X[m] - X[M]) ** 2 / (M - 1)

    ss = 0
    for m in range(1, M + 1):
        ss += (X[m] - X[M]) ** 2
    sss = ss / M - 1
    ssss = ss / M
    return X[M], sigma_squared


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    B = []

    for i in range(0, 300):
        B.append([])
        for j in range(0, 300):
            B[i].append(np.random.randint(0, 2))

    B = np.array(B)

    BT = B.transpose()

    A = BT @ B

    frobenius = 2 * (np.linalg.norm(A) ** 2)

    tr = np.trace(A)
    print("trace: {}".format(tr))

    trace_5 = []
    var_5 = []
    trace_10 = []
    var_10 = []
    trace_25 = []
    var_25 = []
    trace_100 = []
    var_100 = []

    for i in range(100):
        trace, var = MonteCarloTrace(A, 5)
        trace_5.append(trace)
        var_5.append(var)

        trace, var = MonteCarloTrace(A, 10)
        trace_10.append(trace)
        var_10.append(var)

        trace, var = MonteCarloTrace(A, 25)
        trace_25.append(trace)
        var_25.append(var)

        trace, var = MonteCarloTrace(A, 100)
        trace_100.append(trace)
        var_100.append(var)

    print("Varianza stimata con M=(5): {}, frobenius: {}, delta: {}, trace: {}".format(
        var_5[0], frobenius / 5, var_5[0] - frobenius / 5, sum(trace_5) / 100))
    print("Varianza stimata con M=(10): {}, frobenius: {}, delta: {}, trace: {}".format(
        var_10[0] / 100, frobenius / 10, var_10[0] / 100 - frobenius / 10, sum(trace_10) / 100))
    print("Varianza stimata con M=(25): {}, frobenius: {}, delta: {}, trace: {}".format(
        var_25[0] / 100, frobenius / 25, var_25[0] / 100 - frobenius / 25, sum(trace_25) / 100))
    print("Varianza stimata con M=(100): {}, frobenius: {}, delta: {}, trace: {}".format(
        var_100[0] / 100, frobenius / 100, var_100[0] / 100 - frobenius / 100, sum(trace_100) / 100))

    weights = np.ones_like(trace_100) / float(len(trace_100))

    plt.title("5")
    plt.hist(trace_5, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65)
    plt.axvline(tr, color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr - np.sqrt(var_5[0]), color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr + np.sqrt(var_5[0]), color='k', linestyle='dashed', linewidth=1)
    plt.show()

    plt.title("5 var")
    plt.hist(var_5, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65, bins=25)
    plt.axvline(frobenius / 5, color='k', linestyle='dashed', linewidth=1)
    plt.show()


    plt.title("10")
    plt.hist(trace_10, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65)
    plt.axvline(tr, color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr - np.sqrt(var_10[0]), color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr + np.sqrt(var_10[0]), color='k', linestyle='dashed', linewidth=1)
    plt.show()

    plt.title("10 var")
    plt.hist(var_10, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65, bins=25)
    plt.axvline(frobenius / 10, color='k', linestyle='dashed', linewidth=1)
    plt.show()

    plt.title("25")
    plt.hist(trace_25, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65)
    plt.axvline(tr, color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr - np.sqrt(var_25[0]), color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr + np.sqrt(var_25[0]), color='k', linestyle='dashed', linewidth=1)
    plt.show()

    plt.title("25 var")
    plt.hist(var_25, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65, bins=25)
    plt.axvline(frobenius / 25, color='k', linestyle='dashed', linewidth=1)
    plt.show()

    plt.title("100")
    plt.hist(trace_100, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65)
    plt.axvline(tr, color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr - np.sqrt(var_100[0]), color='k', linestyle='dashed', linewidth=1)
    plt.axvline(tr + np.sqrt(var_100[0]), color='k', linestyle='dashed', linewidth=1)
    plt.show()

    plt.title("100 var")
    plt.hist(var_100, weights=weights, color='#E52B50', edgecolor='#FBCEB1', alpha=0.65, bins=25)
    plt.axvline(frobenius / 100, color='k', linestyle='dashed', linewidth=1)
    plt.show()

