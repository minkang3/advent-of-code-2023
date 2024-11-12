#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <tuple>
/*
   Pass in a range, and get a range back. Alter operator[] to return a range, rather
   than just a value. It would have to return a vector of ranges, as it could be
   multiple ranges.
*/

struct Range {
    size_t start, length;
    size_t end;

    Range(size_t start, size_t end)
    : start{start}, end{end} {
        //end = start + length;
        length = end - start;
    }


    friend std::ostream& operator<<(std::ostream& out, Range& r) {
        out << "[" << r.start << ", " << r.end << ") " << r.length;
        return out;
    }
};

struct MapRange {
    size_t dest_range_start, source_range_start, range_length;

    MapRange(size_t dest_start, size_t source_start, size_t range)
        : dest_range_start(dest_start)
        , source_range_start(source_start)
        , range_length(range) {}

    bool operator <(const MapRange r) const{
        return this->source_range_start < r.source_range_start;
    }

    bool in_range(size_t n) {
        return (n >= source_range_start && n < source_range_start + range_length);
    }

    size_t operator[](size_t index) {
        size_t diff = index - source_range_start;
        return dest_range_start + diff;
    }

    Range find_value_range_from_key_range(Range range/*, std::vector<Range>& ranges_vec*/) {
        // First find the range that coincides with this MapRange
        // TODO: Implement this function
        assert(in_range(range.start));

        size_t offset_from_start = range.start - source_range_start;
        Range result_range{dest_range_start + offset_from_start, dest_range_start + offset_from_start + range.length};
        return result_range;
    }


    friend std::ostream& operator<<(std::ostream& out, MapRange& r) {
        out << r.dest_range_start << ' ' << r.source_range_start << ' ' << r.range_length << '\n';
        return out;
    }
};


class Map {
private:
    std::set<MapRange> ranges; 
    std::string name;
public:
    Map() {}

    void insert_range(MapRange range) {
        ranges.insert(range);
    }

    void print_ranges() {
        for (auto r : ranges) {
            std::cout << r;
        }
    }

    size_t operator[](size_t index) {
        for (MapRange r : ranges) {
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

    void find_value_ranges_from_key_range(Range key_range, std::vector<Range>& ranges_vec) {
        for (MapRange MR : ranges) {
            if (MR.source_range_start >= key_range.end)
                break;

            if (MR.in_range(key_range.start)) {
                // If end of range is included within MapRange, just pass whole range in
                if (key_range.end <= MR.source_range_start + MR.range_length) {
                    Range result_range = MR.find_value_range_from_key_range(key_range);
                    ranges_vec.push_back(result_range);
                } else if (key_range.end > MR.source_range_start + MR.range_length) {
                    Range range_within_map_range{key_range.start, MR.source_range_start + MR.range_length};
                    Range range_out_of_map_range{MR.source_range_start + MR.range_length, key_range.end};

                    Range result_range = MR.find_value_range_from_key_range(range_within_map_range);
                    ranges_vec.push_back(result_range);
                    find_value_ranges_from_key_range(range_out_of_map_range, ranges_vec);
                } else
                    throw "find_value_ranges_from_key_range() from Map threw error";

            }

        }
    }
};


struct Maps {
    std::vector<Range> seeds;

    Map seed_to_soil;
    Map soil_to_fertilizer;
    Map fertilizer_to_water;
    Map water_to_light;
    Map light_to_temperature;
    Map temperature_to_humidity;
    Map humidity_to_location;

    /*
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
    */

    std::vector<Range> 
    find_all_locations() {
        // seed to soil
        std::vector<Range> soil_ranges;
        for (Range seed_range : seeds) {
            seed_to_soil.find_value_ranges_from_key_range(seed_range, soil_ranges);
        }
        // soil to fertilizer
        std::vector<Range> fertilizer_ranges;
        for (Range soil_range : soil_ranges) {
            soil_to_fertilizer.find_value_ranges_from_key_range(soil_range, fertilizer_ranges);
        }
        // fertilizer to water
        std::vector<Range> water_ranges;
        for (Range fertilizer_range : fertilizer_ranges) {
            fertilizer_to_water.find_value_ranges_from_key_range(fertilizer_range, water_ranges);
        }
        // water to light
        std::vector<Range> light_ranges;
        for (Range water_range : water_ranges) {
            water_to_light.find_value_ranges_from_key_range(water_range, light_ranges);
        }
        // light to temperature
        std::vector<Range> temperature_ranges;
        for (Range light_range : light_ranges) {
            light_to_temperature.find_value_ranges_from_key_range(light_range, temperature_ranges);
        }
        // temperature to humidity
        std::vector<Range> humidity_ranges;
        for (Range temperature_range : temperature_ranges) {
            temperature_to_humidity.find_value_ranges_from_key_range(temperature_range, humidity_ranges);
        }
        // humidity to location
        std::vector<Range> location_ranges;
        for (Range humidity_range : humidity_ranges) {
            humidity_to_location.find_value_ranges_from_key_range(humidity_range, location_ranges);
        }
        return location_ranges;
    }

    /*{
        std::vector<size_t> locations;
        for (auto seed_id : seeds) {
            //locations.push_back(find_loc(seed_id));
        }
        return locations;
    }*/
};


std::vector<Range> parse_seeds(const std::string& seed_ids) {
    std::vector<Range> seeds_vec;
    std::istringstream iss{seed_ids};
    std::string token1, token2;

    std::getline(iss, token1, ' '); // Voids first part of string: "seeds: "
    while (std::getline(iss, token1, ' ')) {
        if (!std::getline(iss, token2, ' '))
            break;

        size_t seed_id_start = std::stoul(token1);
        size_t seed_range_length = std::stoul(token2);
        seeds_vec.push_back({seed_id_start, seed_id_start + seed_range_length});
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
        MapRange range{dest_range_start, source_range_start, range_length};
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

    for (auto sr : maps.seeds) {
        std::cout << sr.start << ' ' << sr.length << '\n';
        //std::cout << sr.start << ' ' << sr.end << '\n';
    }

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

size_t find_min_location(const std::vector<Range>& location_ranges) {
    size_t min_loc = -1;
    for (Range loc_range : location_ranges) {
        if (loc_range.start < min_loc) {
            min_loc = loc_range.start;
        }
    }
    return min_loc;
}

int main() {
    Maps maps = parse_file("input.txt");
//    std::vector<size_t> locations = 
    std::vector<Range> location_ranges = maps.find_all_locations();

    size_t min_location = find_min_location(location_ranges);
    std::cout << "Minimum Location: " << min_location << '\n';


//    size_t soil_id = maps.seed_to_soil[91926764];
//    std::cout << "91926764 -> " << soil_id << '\n';
//    soil_id = maps.seed_to_soil[211563684];
//    std::cout << "211563684 -> " << soil_id << '\n';
//    soil_id = maps.seed_to_soil[308146179];
//    std::cout << "308146179 -> " << soil_id << '\n';
//
//    for (auto e : locations) {
//        std::cout << e << '\n';
//    }
//
//    size_t min_location = find_min_location(locations);
//    std::cout << "\n\nMin Location: " << min_location << '\n';
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

