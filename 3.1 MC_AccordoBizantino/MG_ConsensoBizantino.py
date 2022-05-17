# Considera il caso di un sistema distribuito costituito da n=4 processi di cui il quarto è inaffidabile. I tre processi affidabili seguono 
# fedelmente il protocollo MonteCarlo mentre il processo inaffidabile, a ogni round, spedisce al processo affidabile i (con i=1,2 e 3) il bit 1-b(i). 
# non più 2021:
# Implementa i tre processi affidabili e calcola media e varianza del numero di round necessari per raggiungere l'accordo. Determina empiricamente il 
# numero di round dopo il quale la probabilità che l'accordo è raggiunto è più grande del 99.9% e cerca di dare una spiegazione al risultato ottenuto

# 2021
# Considera il caso di un sistema distribuito costituito da n=4 processi di cui il quarto è inaffidabile. I tre processi affidabili seguono 
# fedelmente il protocollo MonteCarlo mentre il processo inaffidabile, a ogni round, spedisce al processo affidabile j (con j=1,2 e 3) il bit 1-b(j). 
# Considera R=2^10 run in cui l'accordo è raggiunto in r=1,... round. Spiega il motivo per cui la frazione in cui l'accordo è raggiunto in r round
#  è all'incirca (R/2^r)


import random

results = []
iterations = 10000
HEAD = 1
TAILS = 0
HONESTPROCESS = 3
GlobalCoin = random.randint(0, 1)
Generals = [[],[],[],[]] # list of lists
maj = [] # list
tally = [] # list
GENLENGTH = len(Generals)-1
neededRounds = 0

def most_frequent(mylist):
    counter = {}
    for element in mylist:
        if element in counter.keys():
            counter[element]+=1
        else:
            counter[element] = 1
    if counter.get(0) == counter.get(1):
        return random.randint(0,1)
    else:
        return max(counter, key = counter.get)

def main():
   for i in range(iterations):

      for general in Generals:
         general.clear()
      maj.clear()
      tally.clear()

      neededRounds = 0

      while True:
         GlobalCoin = random.randint(0, 1)
         if neededRounds == 0:
               #taking every general's deciosion randomically and transmitting the information to every other general
               for general in range(GENLENGTH):
                  decision = random.randint(0, 1)
                  for otherGeneral in range(GENLENGTH):
                     Generals[otherGeneral].append(decision)

               #setting up the last general's decision for every general (it should be the opposite of the i-th general)
               for general in range(GENLENGTH):
                  Generals[general].append(1-Generals[general][general]) 
         
         #this is the termination's condition, if there is a majority among the generals' decisions
         if Generals[0][0] == Generals[1][1] == Generals[2][2]:
               results.append(neededRounds)
               break

         #setting up maj to rappresent the majority inside the generals' decisions
         #setting up tally to take be the number of times that the maj value shows up
         most_freqElement = 0
         for general in range(GENLENGTH):
               maj.append(most_frequent(Generals[general]))
               tally.append(Generals[general].count(maj[most_freqElement]))
               most_freqElement+=1

         #taking every general's decision based on the majority or on the value of the global coin
         resultingDecisions = []
         for decisions in range(len(tally)):
               if tally[decisions] >= HONESTPROCESS:
                  resultingDecisions.append(maj[decisions])
               elif GlobalCoin == HEAD:
                  resultingDecisions.append(1)
               else:
                  resultingDecisions.append(0)
         
         #resetting the generals with the new values
         for element in Generals:
               element.clear()

         general_i_decision = 0
         for general in range(GENLENGTH):
               decision = resultingDecisions[general_i_decision]
               for otherGeneral in range(GENLENGTH):
                  Generals[otherGeneral].append(decision)
               general_i_decision+=1

         #setting up the last General, the impostor for every general
         for general in range(GENLENGTH):
               Generals[general].append(1-Generals[general][general]) 

         maj.clear()
         tally.clear()
         neededRounds+=1

   roundsProbabilities = {}
   totalRounds = 0
   variance = 0    
   for element in results:
      totalRounds+= element

   for element in results:
      variance += (pow((element-(totalRounds/iterations)),2) * 1/iterations)
      roundsProbabilities[element] = results.count(element)


   roundcounter = 0
   dictionary_items = roundsProbabilities.items()
   sorted_dict = dict (sorted(dictionary_items))

   #calculating the number of rounds after that the probability of reaching a decision is beyond 99.9%
   finalvalue = 0
   for key in sorted_dict:
      roundcounter += sorted_dict[key]
      if roundcounter >= (iterations - iterations * 0.001):
         finalvalue = key
         break

   print()
   # print(f"La media del numero di round necessari per ottenere l'accordo è {totalRounds/iterations}")
   # print (f"La varianza del numero di round necessari per ottenere l'accordo è di {variance}")
   # print (f"Il numero di round dopo il quale la probabilità che l'accordo sia raggiunto è più grande del 99.9% è {finalvalue}")
   print()
main()