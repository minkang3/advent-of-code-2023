#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <tuple>


struct Range {
    size_t dest_range_start, source_range_start, range_length;

    Range(size_t dest_start, size_t source_start, size_t range)
        : dest_range_start(dest_start)
        , source_range_start(source_start)
        , range_length(range) {}

    bool operator <(const Range r) const{
        return this->source_range_start < r.source_range_start;
    }

    bool in_range(size_t n) {
        return (n >= source_range_start && n < source_range_start + range_length);
    }

    size_t operator[](size_t index) {
        size_t diff = index - source_range_start;
        return dest_range_start + diff;
    }

    friend std::ostream& operator<<(std::ostream& out, Range& r) {
        out << r.dest_range_start << ' ' << r.source_range_start << ' ' << r.range_length << '\n';
        return out;
    }
};


class Map {
private:
    std::set<Range> ranges; 
    std::string name;
public:
    Map() {}

    void insert_range(Range range) {
        ranges.insert(range);
    }

    void print_ranges() {
        for (auto r : ranges) {
            std::cout << r;
        }
    }
/*
    size_t at(size_t index) {
        
    }
*/
    size_t operator[](size_t index) {
        for (Range r : ranges) {
            if (r.source_range_start > index)
                break;
            //std::cout << "Accessing range: " << r;
            if (r.in_range(index)) {
                //std::cout << "Index in range where index: " << index << '\n';
                //std::cout<< index << " -> " << r[index] << '\n';
                return r[index];
            }
            
        }
        //std::cout<< index << " -> " << index << "\n";
        return index;
    }
};


struct Maps {
    std::vector<size_t> seeds;

    Map seed_to_soil;
    Map soil_to_fertilizer;
    Map fertilizer_to_water;
    Map water_to_light;
    Map light_to_temperature;
    Map temperature_to_humidity;
    Map humidity_to_location;

    size_t find_loc(size_t seed_id) {
        size_t soil_id = seed_to_soil[seed_id];
        size_t fertilizer_id = soil_to_fertilizer[soil_id];
        size_t water_id = fertilizer_to_water[fertilizer_id];
        size_t light_id = water_to_light[water_id];
        size_t temperature_id = light_to_temperature[light_id];
        size_t humidity_id = temperature_to_humidity[temperature_id];
        size_t location_id = humidity_to_location[humidity_id];

        return location_id;
    }

    std::vector<size_t> find_all_locations() {
        std::vector<size_t> locations;
        for (size_t seed_id : seeds) {
            locations.push_back(find_loc(seed_id));
        }
        return locations;
    }
};


std::vector<size_t> parse_seeds(const std::string& seed_ids) {
    std::vector<size_t> seeds_vec;
    std::istringstream iss{seed_ids};
    std::string token;

    std::getline(iss, token, ' '); // Voids first part of string: "seeds: "
    while (std::getline(iss, token, ' ')) {
        size_t seed = std::stoul(token);
        seeds_vec.push_back(seed);
    }
    return seeds_vec;
}

std::tuple<size_t,size_t,size_t> 
tokenize_into_size_t(std::string& line) {
    std::istringstream iss{line};
    size_t s1, s2, s3;
    iss >> s1 >> s2 >> s3;
    return {s1, s2, s3};
}

/*
void map_to_range(size_t dest_range_start, size_t source_range_start, size_t range_length,
                    std::map<size_t, size_t>& mp) {
    size_t dest = dest_range_start;
    size_t src = source_range_start;
    for (;dest < dest_range_start + range_length && src < source_range_start + range_length;
            ++dest, ++src) {
        std::cout << "Dest: " << dest << ", Source: " << src << '\n';
        mp[src] = dest;
    }
}
*/
//void
Map
parse_data_to_map(std::ifstream& in) {
    Map mp;
    std::string line;
    while (std::getline(in, line) && line != "") {
        auto [dest_range_start, source_range_start, range_length] = 
            tokenize_into_size_t(line);
        Range range{dest_range_start, source_range_start, range_length};
        mp.insert_range(range);
    }
    return mp;
}

Maps parse_file(std::string file_name) {
    Maps maps;
    std::ifstream in{file_name};
    std::string line;
    std::getline(in, line);

    maps.seeds = parse_seeds(line);

    while (std::getline(in, line)) {
        if (line == "\n") {
            std::cerr << "skipped line\n";
            continue;
        }
        // Pass in ifstream into each function, loop until getline returns empty
        // line, exit out of function then.
        if (line=="seed-to-soil map:") {
            maps.seed_to_soil = parse_data_to_map(in);
        } else if (line=="soil-to-fertilizer map:") {
            maps.soil_to_fertilizer = parse_data_to_map(in);
        } else if (line=="fertilizer-to-water map:") {
            maps.fertilizer_to_water = parse_data_to_map(in);
        } else if (line=="water-to-light map:") {
            maps.water_to_light = parse_data_to_map(in);
        } else if (line=="light-to-temperature map:") {
             maps.light_to_temperature = parse_data_to_map(in);
        } else if (line=="temperature-to-humidity map:") {
             maps.temperature_to_humidity = parse_data_to_map(in);
        } else if (line=="humidity-to-location map:") {
             maps.humidity_to_location = parse_data_to_map(in);
        }
    }
    return maps;
}

size_t find_min_location(const std::vector<size_t>& locations) {
    size_t min = locations[0];
    for (size_t location_id : locations) {
        if (location_id < min) {
            min = location_id;
        }
    }
    return min;
}

int main() {
    Maps maps = parse_file("input.txt");
    //size_t loc = maps.find_loc(3279509610);
    std::vector<size_t> locations = maps.find_all_locations();

    for (auto e : locations) {
        std::cout << e << '\n';
    }

    size_t min_location = find_min_location(locations);
    std::cout << "\n\nMin Location: " << min_location << '\n';
}











//    std::cout << "seed_to_soil\n";
//    maps.seed_to_soil.print_ranges();
//    std::cout << "\n" << "soil_to_fertilizer\n";
//    maps.soil_to_fertilizer.print_ranges();
//    std::cout << "\n" << "fertilizer_to_water\n";
//    maps.fertilizer_to_water.print_ranges();
//    std::cout << "\n" << "water_to_light\n";
//    maps.water_to_light.print_ranges();
//    std::cout << "\n" << "light_to_temperature\n";
//    maps.light_to_temperature.print_ranges();
//    std::cout << "\n" << "temperature_to_humidity\n";
//    maps.temperature_to_humidity.print_ranges();
//    std::cout << "\n" << "humidity_to_location\n";
//    maps.humidity_to_location.print_ranges();
