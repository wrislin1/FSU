SELECT H.address
FROM  House H,Listings L
WHERE H.address = L.address;

SELECT L.address,L.mlsNumber
FROM House H, Listings L
WHERE H.address = L.address;

SELECT H.address
FROM House H, Listings L
WHERE H.address = L.address AND H.bedrooms = 3 AND H.bathrooms = 2;

SELECT P.address, P.price
FROM House H, Property P
WHERE P.address = H.address AND H.bedrooms = 3 AND H.bathrooms = 2
AND P.price > 100000 AND p.price < 199999
ORDER BY P.price DESC;

SELECT B.address, P.price
FROM BusinessProperty B, Property P
WHERE P.address = B.address AND B.type = 'Office Space'
ORDER BY P.price DESC;

SELECT A.name, A.id AS agentid,A.phone,A.dateStarted,F.id AS firmid
FROM Agent A, Firm F
WHERE A.firmid = F.id;

SELECT L.address
FROM Listings L
WHERE agentid =  101;

SELECT A.name AS `Agent`, B.name AS `Buyer`
FROM Agent A, WorksWith W, Buyer B
WHERE A.id = W.agentid AND B.id = W.buyerid;

SELECT P.address,P.price
FROM House H,Buyer B,Property P
WHERE B.id = 3696 AND B.bedrooms = H.bedrooms AND
B.bathrooms = H.bathrooms AND H.address = P.address AND
P.price  >  B.minimumPreferredPrice AND 
P.price < B.maximumPreferredPrice;




