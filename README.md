# Linked-List
Project that was developed using a doubly linked list and queues

Failfish are small monsters that eat only other Failfish. This makes them ecologically and practically useless, causing
many small monster scholars to wonder how they ever came to exist in the first place.

They are delicious, which is a plus, but since they eat each other, they’re almost impossible to farm. That doesn’t keep
people from trying. It keeps them from succeeding, but not from trying.

You have been hired by an ambitious small monster farmer to record their attempts to farm Failfish.

The farmer has:

• Ten Failfish ponds arranged one after the other.
 
    o Each pond has a name, and also a sequence number from 1 to 10.

• 𝐺 groups of Failfish that they’ve captured. Groups of Failfish are called Failgroups. They were called 
Failschools once, but small monster scholars determined that Failfish are unable to learn.

    o Each Failgroup 𝑔𝑖 has 𝑛𝑖 Failfish in it, with 𝑛𝑖 ≥ 2. Note that 𝑖 is the pond number – the Failfish don’t
    have to be in ponds 1. . 𝐺.
    
    o Each Failfish in a Failgroup is branded with a sequence number, from 1 to 𝑛𝑖
    
▪ (Modern small monster farming methods being humane, the branding is done with a particularly waterproof marker. No Failfish are harmed during modern Failfish farming. (Except when they get eaten.))

The Meal, First Course:

Failfish in a Failgroup form a Failcircle when preparing to eat each other. For a group of seven Failfish, the Failcircle looks like Figure 1.
Once a Failcircle is formed, phase 1 of the dining begins. It’s controlled by three values: 𝑒𝑖 , the eating counter; 𝑡ℎ𝑖 , the minimum Failgroup threshold;
and 𝑛𝑖 , the number of Failfish.

• The Failfish begin counting with the smallest-numbered Failfish in the Failcircle.

• The Failfish skip the first 𝑒𝑖 − 1 Failfish, and eat the 𝑒𝑖th Failfish clockwise of the starting Failfish.

• The Failfish then skip the next 𝑒𝑖 − 1 fish, and eat the 𝑒𝑖 th Failfish clockwise of the last-eaten Failfish.

• This process continues until the Failcircle’s population drops to 𝑡ℎ𝑖, the minimum Failgroup threshold. Each Failgroup dines independently according to this algorithm. No one is quite sure why. The fish will continue to eat each other until the population of the group is reduced to a threshold value 𝑡ℎ𝑖. Uneaten
fish at this point continue to the second course.
