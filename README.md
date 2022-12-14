# Linked-List
Project that was developed using a doubly linked list and queues

Failfish are small monsters that eat only other Failfish. This makes them ecologically and practically useless, causing
many small monster scholars to wonder how they ever came to exist in the first place.

They are delicious, which is a plus, but since they eat each other, theyβre almost impossible to farm. That doesnβt keep
people from trying. It keeps them from succeeding, but not from trying.

You have been hired by an ambitious small monster farmer to record their attempts to farm Failfish.

The farmer has:
* Ten Failfish ponds arranged one after the other.
  * Each pond has a name, and also a sequence number from 1 to 10.
* πΊ groups of Failfish that theyβve captured. Groups of Failfish are called Failgroups. They were called  Failschools once, but small monster scholars determined that Failfish are unable to learn.
  * Each Failgroup π<sub>π</sub> has π<sub>π</sub> Failfish in it, with π<sub>π</sub> β₯ 2. Note that π is the pond number β the Failfish donβt
    have to be in ponds 1...πΊ.
  * Each Failfish in a Failgroup is branded with a sequence number, from 1 to π<sub>π</sub>
* (Modern small monster farming methods being humane, the branding is done with a particularly waterproof marker. No Failfish are harmed during modern Failfish farming. (Except when they get eaten.))

### The Meal, First Course: ###

Failfish in a Failgroup form a Failcircle when preparing to eat each other. For a group of seven Failfish, the Failcircle looks like Figure 1.
Once a Failcircle is formed, phase 1 of the dining begins. Itβs controlled by three values: π<sub>π</sub> , the eating counter; π‘β<sub>π</sub> , the minimum Failgroup threshold; and π<sub>π</sub> , the number of Failfish.
* The Failfish begin counting with the smallest-numbered Failfish in the Failcircle.
* The Failfish skip the first π<sub>π</sub> β 1 Failfish, and eat the π<sub>π</sub>th Failfish clockwise of the starting Failfish.
* The Failfish then skip the next π<sub>π</sub> β 1 fish, and eat the π<sub>π</sub>th Failfish clockwise of the last-eaten Failfish.
* This process continues until the Failcircleβs population drops to π‘β<sub>π</sub>, the minimum Failgroup threshold. Each Failgroup dines independently according to this algorithm. No one is quite sure why. The fish will continue to eat each other until the population of the group is reduced to a threshold value π‘β<sub>π</sub>. Uneaten fish at this point continue to the second course.

### The Meal, Second Course: ###

At this point the Failcircles unwind into Failqueues, with the smallest-numbered Failfish from each Failcircle at the head of that Failcircleβs Failqueue.
* The Failfish converge on and consume the highest-numbered Failfish of those at the heads of the queues.
* In case of a tie, the Failfish at the head of the smallest-numbered Failgroupβs queue is eaten.
* This continues until there is only one Failfish remaining.
* You are to report which Failfish this is, based on the theory that this information will allow the farmer to breed Failfish that are less likely to be eaten.
  * (It will not.)
