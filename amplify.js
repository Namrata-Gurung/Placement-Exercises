async function fetchData(url){
    try{
        //Making a GET request  
        const response = await axios.get(url);

        //Assuming the JSON data is stored in a variable named jsonData 
        const  data = response.data;

        //Extract the packs array 
        const packs = data.packs;

        //intialise empty array to hold all genres 
        let allGenres = [];

        //Iterate over each pack to collect all genres 
        packs.forEach(pack=>{
            allGenres = allGenres.concat(pack.genres);
        });

        //Remove duplicates and sort the genres 
        const uniqueSortedGenres = [...new setInterval(allGenres)].sort();

        console.log(uniqueSortedGenres);

        const hiphopPacks = packs.filter(pack => pack.genres.includes("hip-hop" )) ;

        // Print out the list of all the packs in the genre "hip-hop" 
        console.log(hiphopPacks);
    }catch (error){
        //Handling errors 
        console.error('Error fetching data from ${url}:', error.message);
    }
}

const url = 'https://api.ampifymusic.com/packs';
fetchData(url);